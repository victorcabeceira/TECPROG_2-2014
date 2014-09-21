#include "EnemyStateIdle.h"
#include <cmath>
#include "SDLWrapper.h"
#include "Logger.h"

void EnemyStateIdle::enter(){

	this->enemy->isGrounded = true;

	if(enemy->life <= 0){
	
		enemy->vy = 0;
		enemy->changeState(Enemy::EStates::DEAD);
	
	}
}

void EnemyStateIdle::exit(){
}

void EnemyStateIdle::update(const double dt_){

	((void)dt_); // Unused.
	
	// Aerial
	if(!this->enemy->isGrounded){
		
		this->enemy->changeState(Enemy::EStates::AERIAL);
		return;
	
	}

	/// @todo Make the range be only in the direciton the enemy is facing.
	if(abs(this->enemy->x - Enemy::px) < Enemy::alertRange){
	
		this->enemy->changeState(Enemy::EStates::ALERT);
		return;
	
	}
	else if(abs(this->enemy->x - Enemy::px) < Enemy::curiousRange){
	
		this->enemy->changeState(Enemy::EStates::CURIOUS);
		return;
	
	}

}

EnemyStateIdle::EnemyStateIdle(Enemy* const enemy_) :
	
	StateEnemy(enemy_)
{
}
