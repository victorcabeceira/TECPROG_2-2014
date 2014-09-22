#include "EnemyStatePatrolling.h"
#include <cfloat>
#include "Logger.h"

void EnemyStatePatrolling::enter(){

	this->enemy->isGrounded = true;
	this->enemy->x = this->enemy->originalX;
	this->direction = 1.0;

	if(enemy->life <= 0){

		enemy->vy = 0;
		enemy->changeState(Enemy::EStates::DEAD);

	}
}

void EnemyStatePatrolling::exit(){
}

void EnemyStatePatrolling::update(const double deltaTime_){

	((void)deltaTime_); // Unused.
	
	// Patrol.
	if(abs(this->enemy->x - this->enemy->originalX) > this->enemy->patrolLength){
	
		// right
		if(this->enemy->x - this->enemy->originalX < 0.0){
	
			this->direction = 1.0;
	
		}
		// left
		else{
	
			this->direction = -1.0;
	
		}	
	}
	else{
		// Do nothing.
	}

	this->enemy->vx += this->enemy->speed * this->direction;

	/// @todo Make the range be only in the direciton the enemy is facing.
	if(abs(this->enemy->x - Enemy::px) < Enemy::alertRange && abs(this->enemy->y - Enemy::py) < Enemy::alertRange){
	
		this->enemy->changeState(Enemy::EStates::ALERT);
		return;
	
	}
	
	else if(abs(this->enemy->x - Enemy::px) < Enemy::curiousRange && abs(this->enemy->y - Enemy::py) < Enemy::curiousRange){
	
		this->enemy->changeState(Enemy::EStates::CURIOUS);
		return;
	
	}
}

EnemyStatePatrolling::EnemyStatePatrolling(Enemy* const enemy_) :

	StateEnemy(enemy_),
	direction(0.0)
{
}
