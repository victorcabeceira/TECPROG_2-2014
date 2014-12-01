#include "EnemyStatePatrolling.h"
#include <cfloat>
#include "Logger.h"

//Enters the Patrolling State - Constructor
void EnemyStatePatrolling::enter(){

	this->enemy->isGrounded = true;
	this->enemy->x = this->enemy->originalX;
	this->direction = 1.0;

	if(enemy->life <= 0){

		enemy->vy = 0;
		enemy->changEnemyState(Enemy::EnemyStates::DEAD);

	}
}

//Exits the Patrolling State - Destructor
void EnemyStatePatrolling::exit(){
}


//Updates the Patrolling State - Constructor
void EnemyStatePatrolling::update(const double deltaTime_){

	((void)deltaTime_); // Unused.
	
	int enemyPatrolArea = this->enemy->x - this->enemy->originalX;

	// Patrol.
	if(abs(enemyPatrolArea) > this->enemy->patrolLength){
	
		// right
		if(enemyPatrolArea < 0.0){
	
			this->direction = RIGHT_DIRECTION;
	
		}
		// left
		else{
	
			this->direction = LEFT_DIRECTION;
	
		}	
	}
	else{
		// Do nothing.
	}

	this->enemy->vx += this->enemy->speed * this->direction;

	/// @todo Make the range be only in the direciton the enemy is facing.
	if(abs(this->enemy->x - Enemy::px) < Enemy::alertRange && 
	   abs(this->enemy->y - Enemy::py) < Enemy::alertRange){
	
		this->enemy->changEnemyState(Enemy::EnemyStates::ALERT);
		return;
	
	}
	
	else if(abs(this->enemy->x - Enemy::px) < Enemy::curiousRange &&
			abs(this->enemy->y - Enemy::py) < Enemy::curiousRange){
	
		this->enemy->changEnemyState(Enemy::EnemyStates::CURIOUS);
		return;
	
	}
}

EnemyStatePatrolling::EnemyStatePatrolling(Enemy* const enemy_) :

	StateEnemy(enemy_),
	direction(0.0)
{
}
