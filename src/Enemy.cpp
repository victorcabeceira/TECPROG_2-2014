#include "Enemy.h"
#include "Logger.h"
#include "LuaScript.h"
#include <cmath>

#include "EnemyStateIdle.h"
#include "EnemyStatePatrolling.h"
#include "EnemyStateAerial.h"
#include "EnemyStateCurious.h"
#include "EnemyStateAlert.h"
#include "EnemyStateAttack.h"
#include "EnemyStateDead.h"

#include "Window.h"

#define ADD_STATE_EMPLACE(stateEnum, stateClass) this->statesMap.emplace(stateEnum, new stateClass(this))
#define ADD_STATE_INSERT(stateEnum, stateClass) this->statesMap.insert(std::make_pair<EnemyStates, StateEnemy*>(stateEnum, new stateClass(this)));

double Enemy::px = 0.0;
double Enemy::py = 0.0;
unsigned int Enemy::pLife = 3;
bool Enemy::pVulnerable = false;
double Enemy::alertRange = 300.0;
double Enemy::curiousRange = 600.0;

Enemy::Enemy(const double x_, const double y_, const std::string& path_, const bool patrol_,
	const double patrolLength_) :

	DynamicEntity(x_, y_, path_),
	originalX(x_),
	patrol(patrol_),
	patrolLength(patrolLength_),
	life(100),
	currentState(nullptr),
	animation(nullptr),
	statesMap(),
	dead(false)

{

	initializEnemyStates();

	this->speed = 3.0;

	LuaScript luaEnemy("lua/Enemy.lua");
	this->width = luaEnemy.unlua_get<int>("enemy.dimensions.width");
	this->height = luaEnemy.unlua_get<int>("enemy.dimensions.height");

	this->animation = new Animation(0, 0, this->width, this->height, 0, false);

	if(this->patrol){

		this->currentState = this->statesMap.at(PATROLLING);

	}
	else{

		this->currentState = this->statesMap.at(IDLE);

	}
	
	this->currentState->enter();

}

Enemy::~Enemy(){

	if(this->currentState != nullptr){

		this->currentState->exit();
		this->currentState = nullptr;

	}

	if(this->animation != nullptr){

        delete this->animation;
        this->animation = nullptr;

    }

	destroyStates();

}

void Enemy::update(const double deltaTime_){
	
	this->currentState->update(deltaTime_);
	forceMaxSpeed();

	scoutPosition(deltaTime_);

	this->animation->update(this->animationClip, deltaTime_);

	updateBoundingBox();

	const std::array<bool, CollisionSide::SOLID_TOTAL> detections = detectCollision();
	handleCollision(detections);

	updatePosition(deltaTime_);

}

void Enemy::render(const double cameraX_, const double cameraY_){

	const double dx = this->x - cameraX_;
	const double dy = this->y - cameraY_;

	///////////////////////////////////////////////////////////////////////////////////////////
	// // Actual.
	// SDL_Rect actualRect = {(int)dx, (int)dy, (int)this->width, (int)this->height};
	// SDL_SetRenderDrawColor( Window::getRenderer(), 0x00, 0x00, 0x00, 0xFF);
	// SDL_RenderFillRect(Window::getRenderer(), &actualRect);

	// Bounding box.
	// SDL_Rect boundingBox2 = {(int)(this->boundingBox.x - cameraX_), (int)(this->boundingBox.y - cameraY_), (int)this->boundingBox.w, (int)this->boundingBox.h};
	// SDL_SetRenderDrawColor( Window::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	// SDL_RenderFillRect(Window::getRenderer(), &boundingBox2);
	// ///////////////////////////////////////////////////////////////////////////////////////////

	if(this->sprite != nullptr){

		SDL_RendererFlip flip = getFlip();

		if(flip == SDL_FLIP_HORIZONTAL)

			this->sprite->render(dx - 120, dy, &this->animationClip, false, 0.0, nullptr, flip);

		else

			this->sprite->render(dx, dy, &this->animationClip, false, 0.0, nullptr, flip);

	}
}

void Enemy::initializEnemyStates(){

	// Initialize all the states in Enemy here.
	ADD_STATE_INSERT(IDLE,         EnemyStateIdle);
	ADD_STATE_INSERT(CURIOUS,      EnemyStateCurious);
	ADD_STATE_INSERT(PATROLLING,   EnemyStatePatrolling);
	ADD_STATE_INSERT(ALERT,        EnemyStateAlert);
	ADD_STATE_INSERT(AERIAL,       EnemyStateAerial);
	ADD_STATE_INSERT(ATTACK,       EnemyStateAttack);
	ADD_STATE_INSERT(DEAD,         EnemyStateDead);

}

void Enemy::destroyStates(){

	// Delete all the states in Enemy here.
	std::map<EnemyStates, StateEnemy*>::const_iterator it;
	for(it = this->statesMap.begin(); it != this->statesMap.end(); it++){

		delete it->second;

	}
}

void Enemy::changEnemyState(const EnemyStates state_){

	this->currentState->exit();
	this->currentState = this->statesMap.at(state_);
	this->currentState->enter();

}

void Enemy::handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_){

	if(detections_.at(CollisionSide::SOLID_TOP)){ 

		this->vy = 0.0;

	}

	if(detections_.at(CollisionSide::SOLID_BOTTOM)){

		if(this->currentState == this->statesMap.at(EnemyStates::AERIAL) || this->currentState == this->statesMap.at(EnemyStates::DEAD)){

			this->nextY -= fmod(this->nextY, 64.0) - 16.0;
			this->vy = 0.0;

			if(this->isDead()){

				this->changEnemyState(EnemyStates::DEAD);

			}

			if(this->patrol){

				this->changEnemyState(EnemyStates::PATROLLING);

			}
			else{

				this->changEnemyState(EnemyStates::IDLE);
				return;

			}
		}
	}
	else{

		if(this->currentState != this->statesMap.at(EnemyStates::AERIAL)){

			changEnemyState(EnemyStates::AERIAL);

		}
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

void Enemy::forceMaxSpeed(){

	this->vx = (this->vx >= this->maxSpeed) ? this->maxSpeed : this->vx ;
	this->vy = (this->vy >= this->maxSpeed) ? this->maxSpeed : this->vy ;

}

Animation *Enemy::getAnimation(){

	return (this->animation);

}

void Enemy::setDead(bool isDead_){

	this->dead = isDead_;

}

bool Enemy::isDead(){

	return this->dead;

}

void Enemy::updateBoundingBox(){

	this->boundingBox.x = (int) this->nextX + 40;
	this->boundingBox.y = (int) this->nextY + 40;
	this->boundingBox.w = 150;
	this->boundingBox.h = 200;

}
