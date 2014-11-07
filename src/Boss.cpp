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
#include "SafeDeallocation.h"

#include "Window.h"

#define ADD_STATE_EMPLACE(stateEnum, stateClass) this->statesMap.emplace(stateEnum, new stateClass(this))
#define ADD_STATE_INSERT(stateEnum, stateClass) this->statesMap.insert(std::make_pair<BossStates, StateBoss*>(stateEnum, new stateClass(this)));

// Method that creates the Boss of the game.
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

	//Starts the first state of the boss on it's state machine.
	initializEnemyStates();

	// Set the initial values for the boss
	this->isRight = true;
	this->speed = 400.0;
	this->width = 360;
	this->height = 360;

	// Creates the animation of the boss.
	this->animation = new Animation(0, 0, this->width, this->height, 7, false);
	this->powerAnimation = new Animation(0, 0, 0, 0, 0, false);
	this->shieldAnimation = new Animation(0, 0, 340, 340, 6, false);
	this->shield = Game::instance().getResources().get("res/images/shield.png");
	this->shieldAnimation->changeAnimation(0,0,3,false,1);

	// Set the current state as IDLE.
	this->currentState = this->statesMap.at(IDLE);
	this->currentState->enter();

	// Make sure the player is not null.
	if(this->player == nullptr){

		Log(WARN) << "Passing a null player to the Boss.";

	}
}

//Destructor method, runs when the class is deallocated
Boss::~Boss(){
	
	SAFE_DELETE(this->animation);
	SAFE_DELETE(this->powerAnimation);
	SAFE_DELETE(this->shieldAnimation);
	SAFE_EXIT(this->currentState);
	
	this->player = nullptr;

	destroyStates();

}

//Updates the position and animation of the Boss
void Boss::update(const double deltaTime_){

	// Check if the boss can move without physically hits anything.
	scoutPosition(deltaTime_);

	// Update the boss animation.
	this->animation->update(this->animationClip, deltaTime_);
	this->powerAnimation->update(this->powerClip, deltaTime_);
	this->shieldAnimation->update(this->shieldClip, deltaTime_);

	// Set the collision limits of the boss.
	updateBoundingBox();

	// Detect collisions with walls, floor and player.
	const std::array<bool, CollisionSide::SOLID_TOTAL> detections = detectCollision();
	handleCollision(detections);

	// Update the boss position.
	updatePosition(deltaTime_);

	// Update the current state of the boss.
	this->currentState->update(deltaTime_);

    for(auto potion : this->potions){

        if(!potion->activated){
            // Delete potion.

        }

        potion->update(deltaTime_);

    }
}

// Render the boss's sprites.
void Boss::render(const double cameraX_, const double cameraY_){

	// Get the relative position of the boss.
	const double dx = this->x - cameraX_;
	const double dy = this->y - cameraY_;
	
	// Check if sprite is not null.
	if(this->sprite != nullptr){

		SDL_RendererFlip flip = getFlip();

		// If the boss is going right, render.
		if(flip == SDL_FLIP_HORIZONTAL){

			this->sprite->render(dx - 120, dy, &this->animationClip, false, 0.0, nullptr, flip);

		}
		// If the boss is going left, render.
		else{

			this->sprite->render(dx, dy, &this->animationClip, false, 0.0, nullptr, flip);

		}
	}
	
	// Render the boss's shield.
	renderShield(dx, dy);

	// Get the relative position of the boss's power.
	const double pdx = this->powerX - cameraX_;
	const double pdy = this->powerY - cameraY_;

	// Check if sprite is not null and if the power is activated.
	if(this->power != nullptr && this->powerIsActivated){
		
		// If the boss is going right, render.
		if(this->powerFlip == SDL_FLIP_HORIZONTAL){

			this->power->render(pdx - this->powerClip.w, pdy, &this->powerClip, false, 0.0, nullptr, this->powerFlip);

		}
		// If the boss is going left, render.
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

	// Check if the shield is activated.
	if(this->hasShield){

		SDL_RendererFlip flip = getFlip();

		// If the boss is going right, render.		
		if(flip == SDL_FLIP_HORIZONTAL){

			this->shield->render(dx, dy, &this->shieldClip);

		}
		// If the boss is going left, render.
		else{

			this->shield->render(dx -120, dy, &this->shieldClip);

		}
	}
}

// Initialize all the states in Boss here.
void Boss::initializEnemyStates(){

	ADD_STATE_INSERT(IDLE,				BossStateIdle);
	ADD_STATE_INSERT(ATTACK,			BossStateAttack);
	ADD_STATE_INSERT(SHIELD,			BossStateShield);
	ADD_STATE_INSERT(TELEPORT,			BossStateTeleport);
	ADD_STATE_INSERT(ICEPRISION,		BossStateIcePrision);
	ADD_STATE_INSERT(MAGICPROJECTILE,	BossStateMagicProjectile);

}

// Delete all the states in Boss here.
void Boss::destroyStates(){

	std::map<BossStates, StateBoss*>::const_iterator it;

	for(it = this->statesMap.begin(); it != this->statesMap.end(); it++){

		delete it->second;

	}
}

//Changes the States of the Boss.
void Boss::changEnemyState(const BossStates state_){

	this->currentState->exit();
	this->currentState = this->statesMap.at(state_);
	this->currentState->enter();
}

//Handle the Collisions of the player with the Boss.
void Boss::handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_){

	// If collide on top.
	if(detections_.at(CollisionSide::SOLID_TOP)){ 

		this->vy = 0.0;

	}

	// If collide on bottom.
	if(detections_.at(CollisionSide::SOLID_BOTTOM)){

		this->nextY -= fmod(this->nextY, 64.0) - 16.0;
		this->vy = 0.0;

	}

	// If collide on left.
	if(detections_.at(CollisionSide::SOLID_LEFT)){

		this->nextX = this->x;
		this->vx = 0.0;

	}

	// If collide on right.
	if(detections_.at(CollisionSide::SOLID_RIGHT)){

		this->nextX = this->x;
		this->vx = -0.001;

	}
}

//Makes the Boss use the potion.
void Boss::usePotion(const int strength_, const int distance_){

	// Check if still have potions.
    if(this->potionsLeft > 0){

        this->potionsLeft--;
        
        // Get the position of the potion.
        const double potionX = ((this->isRight) ? this->boundingBox.x + this->boundingBox.w : this->boundingBox.x);

        // Creates the potion.
        Potion* potion = new Potion(potionX , this->y, "res/images/potion.png", strength_, this->vx, distance_, this->isRight);
        this->potions.push_back(potion);

    }
}

// Return the animation of the boss.
Animation *Boss::getAnimation(){

	return (this->animation);

}

// Set that the boos's life is over :'(.
void Boss::setDead(bool isDead_){

	this->dead = isDead_;

}

// Return if the boss is dead.
bool Boss::isDead(){

	return this->dead;

}

// Update the bounding box of the boss.
void Boss::updateBoundingBox(){

	this->boundingBox.x = (int) this->x + 40;
	this->boundingBox.y = (int) this->y + 40;
	this->boundingBox.w = 150;
	this->boundingBox.h = 200;

}
