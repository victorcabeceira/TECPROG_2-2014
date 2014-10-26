#include "Boss.h"
#include "Logger.h"
#include "Game.h"
#include <cmath>

#include "BossStateIdle.h"
#include "BossStateAttack.h"
#include "BossStateShield.h"
#include "BossStateTeleport.h"
#include "BossStateIcePrision.h"
#include "BossStateMagicProjectile.h"
#include "SafeDelete.h"

#include "Window.h"

#define ADD_STATE_EMPLACE(stateEnum, stateClass) this->statesMap.emplace(stateEnum, new stateClass(this))
#define ADD_STATE_INSERT(stateEnum, stateClass) this->statesMap.insert(std::make_pair<BossStates, StateBoss*>(stateEnum, new stateClass(this)));

Boss::Boss(const double x_, const double y_, const std::string& path_, Player* const player_) :

	DynamicEntity(x_, y_, path_),	
	potionsLeft(3),
	sawPlayer(false),
	potions(),
	life(8),
	hasShield(false),
	canWalk(true),
	player(player_),
	powerAnimation(nullptr),
	powerX(0.0),
	powerY(0.0),
	powerIsActivated(false),
	power(nullptr),
	powerClip{0,0,0,0},
	powerFlip(SDL_FLIP_NONE),
	shieldAnimation(nullptr),
	shield(nullptr),
	shieldClip{0,0,0,0},
	currentState(nullptr),
	animation(nullptr),
	statesMap(),
	dead(false)

{

	//Creates the Boss
	initializEnemyStates();

	this->isRight = true;
	this->speed = 400.0;
	this->width = 360;
	this->height = 360;

	this->animation = new Animation(0, 0, this->width, this->height, 7, false);
	this->powerAnimation = new Animation(0, 0, 0, 0, 0, false);
	this->shieldAnimation = new Animation(0, 0, 340, 340, 6, false);
	this->shield = Game::instance().getResources().get("res/images/shield.png");
	this->shieldAnimation->changeAnimation(0,0,3,false,1);
	this->currentState = this->statesMap.at(IDLE);
	this->currentState->enter();

	if(this->player == nullptr){

		Log(WARN) << "Passing a null player to the Boss.";

	}
}

Boss::~Boss(){

	//Destructor method, runs when the class is deallocated
	
	SAFE_DELETE(this->animation);
	SAFE_DELETE(this->powerAnimation);
	SAFE_DELETE(this->shieldAnimation);

	if(this->currentState != nullptr){

		this->currentState->exit();

	}


	this->player = nullptr;

	destroyStates();

}

//Updates the position and animation of the Boss
void Boss::update(const double deltaTime_){

	scoutPosition(deltaTime_);

	this->animation->update(this->animationClip, deltaTime_);
	this->powerAnimation->update(this->powerClip, deltaTime_);
	this->shieldAnimation->update(this->shieldClip, deltaTime_);

	updateBoundingBox();

	const std::array<bool, CollisionSide::SOLID_TOTAL> detections = detectCollision();
	handleCollision(detections);

	updatePosition(deltaTime_);

	this->currentState->update(deltaTime_);

    for(auto potion : this->potions){

        if(!potion->activated){
            // Delete potion.

        }

        potion->update(deltaTime_);

    }
}

void Boss::render(const double cameraX_, const double cameraY_){

	//Render Boss's sprites

	const double dx = this->x - cameraX_;
	const double dy = this->y - cameraY_;
	
	if(this->sprite != nullptr){

		SDL_RendererFlip flip = getFlip();

		if(flip == SDL_FLIP_HORIZONTAL){

			this->sprite->render(dx - 120, dy, &this->animationClip, false, 0.0, nullptr, flip);

		}
		else{

			this->sprite->render(dx, dy, &this->animationClip, false, 0.0, nullptr, flip);

		}
	}
	
	renderShield(dx, dy);

	const double pdx = this->powerX - cameraX_;
	const double pdy = this->powerY - cameraY_;

	if(this->power != nullptr && this->powerIsActivated){
		
		if(this->powerFlip == SDL_FLIP_HORIZONTAL){

			this->power->render(pdx - this->powerClip.w, pdy, &this->powerClip, false, 0.0, nullptr, this->powerFlip);

		}
		else{

			this->power->render(pdx, pdy, &this->powerClip, false, 0.0, nullptr, this->powerFlip);

		}
	}

    for (auto potion : this->potions) {

        potion->render(cameraX_, cameraY_);

    }
}

// Shield render.
void Boss::renderShield(int dx, int dy){

	if(this->hasShield){

		SDL_RendererFlip flip = getFlip();

		if(flip == SDL_FLIP_HORIZONTAL){

			this->shield->render(dx, dy, &this->shieldClip);

		}
		else{

			this->shield->render(dx -120, dy, &this->shieldClip);

		}
	}
}

void Boss::initializEnemyStates(){

	// Initialize all the states in Boss here.
	ADD_STATE_INSERT(IDLE,				BossStateIdle);
	ADD_STATE_INSERT(ATTACK,			BossStateAttack);
	ADD_STATE_INSERT(SHIELD,			BossStateShield);
	ADD_STATE_INSERT(TELEPORT,			BossStateTeleport);
	ADD_STATE_INSERT(ICEPRISION,		BossStateIcePrision);
	ADD_STATE_INSERT(MAGICPROJECTILE,	BossStateMagicProjectile);

}

void Boss::destroyStates(){

	// Delete all the states in Boss here.
	std::map<BossStates, StateBoss*>::const_iterator it;

	for(it = this->statesMap.begin(); it != this->statesMap.end(); it++){

		delete it->second;

	}
}

void Boss::changEnemyState(const BossStates state_){

	//Changes the States of the Boss

	this->currentState->exit();
	this->currentState = this->statesMap.at(state_);
	this->currentState->enter();
}

void Boss::handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_){

	//Handle the Collisions of the player with the Boss

	if(detections_.at(CollisionSide::SOLID_TOP)){ 

		this->vy = 0.0;

	}

	if(detections_.at(CollisionSide::SOLID_BOTTOM)){

			this->nextY -= fmod(this->nextY, 64.0) - 16.0;
			this->vy = 0.0;

	}

	if(detections_.at(CollisionSide::SOLID_LEFT)){

		this->nextX = this->x;
		this->vx = 0.0;

	}

	if(detections_.at(CollisionSide::SOLID_RIGHT)){

		this->nextX = this->x;
		this->vx = -0.001;

	}
}

void Boss::usePotion(const int strength_, const int distance_){

	//Makes the Boss use the potion

    if(this->potionsLeft > 0){

        this->potionsLeft--;
        const double potionX = ((this->isRight) ? this->boundingBox.x + this->boundingBox.w : this->boundingBox.x);
        Potion* potion = new Potion(potionX , this->y, "res/images/potion.png", strength_, this->vx, distance_, this->isRight);
        this->potions.push_back(potion);

    }
}

Animation *Boss::getAnimation(){

	return (this->animation);

}

void Boss::setDead(bool isDead_){

	this->dead = isDead_;

}

bool Boss::isDead(){

	return this->dead;

}

void Boss::updateBoundingBox(){

	this->boundingBox.x = (int) this->x + 40;
	this->boundingBox.y = (int) this->y + 40;
	this->boundingBox.w = 150;
	this->boundingBox.h = 200;

}
