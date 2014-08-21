#include "EStateAerial.h"
#include "Logger.h"

void EStateAerial::enter(){
	this->enemy->isGrounded = false;
}

void EStateAerial::exit(){

}

void EStateAerial::update(const double dt_){

	((void)dt_); // Unused.

	// Idle
	if(this->enemy->isGrounded){
		if(this->enemy->patrol){
			this->enemy->changeState(Enemy::EStates::PATROLLING);
			return;
		}
		else{
			this->enemy->changeState(Enemy::EStates::IDLE);
			return;
		}
	}

	// Gravity
	this->enemy->applyGravity();
}

EStateAerial::EStateAerial(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}
