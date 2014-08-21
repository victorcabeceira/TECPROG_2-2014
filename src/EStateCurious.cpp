#include "EStateCurious.h"
#include "Logger.h"

#define MAX_CURIOUS_TIME 4.666

void EStateCurious::enter(){
	this->enemy->getAnimation()->changeAnimation(1, 0, 9, false, 1.2);
	this->enemy->speed = 5.0;

	if(enemy->life <= 0){
		enemy->vy = 0;
		enemy->changeState(Enemy::EStates::DEAD);
	}
}

void EStateCurious::exit(){

}

void EStateCurious::update(const double dt_){

	this->timeElapsed += dt_;

	// Aerial
	if(!this->enemy->isGrounded){
		this->enemy->changeState(Enemy::EStates::AERIAL);
		return;
	}

	if(this->enemy->x - Enemy::px < 0.0){
		this->enemy->vx += this->enemy->speed;
	}
	else{
		this->enemy->vx -= this->enemy->speed;
	}

	// 
	if(abs(this->enemy->x - Enemy::px) < Enemy::alertRange && abs(this->enemy->y - Enemy::py) < Enemy::alertRange){
		this->enemy->changeState(Enemy::EStates::ALERT);
		return;
	}

	if(timeElapsed >= MAX_CURIOUS_TIME){
		this->enemy->changeState(Enemy::EStates::PATROLLING);
		return;
	}

}

EStateCurious::EStateCurious(Enemy* const enemy_) :
	StateEnemy(enemy_),
	timeElapsed(0.0)
{

}
