#include "EnemyStateAerial.h"
#include "Logger.h"

//Enters the Aerial State - The Constructor
void EnemyStateAerial::enter(){

	this->enemy->isGrounded = false;

}

//Exits the Aerial State - The Destructor
void EnemyStateAerial::exit(){
}

//Updates the Aerial State
void EnemyStateAerial::update(const double deltaTime_){

	((void)deltaTime_); // Unused.

	// Idle
	if(this->enemy->isGrounded){

		if(this->enemy->patrol){

			this->enemy->changEnemyState(Enemy::EnemyStates::PATROLLING);
			return;

		}
		else{

			this->enemy->changEnemyState(Enemy::EnemyStates::IDLE);
			return;

		}
	}

	// Gravity
	this->enemy->applyGravity();

}

EnemyStateAerial::EnemyStateAerial(Enemy* const enemy_) :

	StateEnemy(enemy_)

{
}
