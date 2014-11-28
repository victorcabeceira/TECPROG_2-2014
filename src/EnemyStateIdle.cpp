#include "EnemyStateIdle.h"
#include <cmath>
#include "SDLWrapper.h"
#include "Logger.h"

// Enter the state and initialize the variables.
void EnemyStateIdle::enter(){

	this->enemy->isGrounded = true;

	if(enemy->life <= 0){
	
		enemy->vy = 0;
		enemy->changEnemyState(Enemy::EnemyStates::DEAD);
	
	}
}

// Exit the state, place to deallocate anything if necessary.
void EnemyStateIdle::exit(){
}

// Updates the state, doing the state logic.
void EnemyStateIdle::update(const double deltaTime_){

	((void)deltaTime_); // Unused.
	
	// Aerial
	if(!this->enemy->isGrounded){
		
		this->enemy->changEnemyState(Enemy::EnemyStates::AERIAL);
		return;
	
	}

	/// @todo Make the range be only in the direciton the enemy is facing.
	if(abs(this->enemy->x - Enemy::px) < Enemy::alertRange){
	
		this->enemy->changEnemyState(Enemy::EnemyStates::ALERT);
		return;
	
	}
	else if(abs(this->enemy->x - Enemy::px) < Enemy::curiousRange){
	
		this->enemy->changEnemyState(Enemy::EnemyStates::CURIOUS);
		return;
	
	}

}

// Constructor of the enemy state idle, sets the enemy.
EnemyStateIdle::EnemyStateIdle(Enemy* const enemy_) :
	
	StateEnemy(enemy_)
{
}
