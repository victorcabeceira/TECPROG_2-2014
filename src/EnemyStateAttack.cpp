#include "EnemyStateAttack.h"
#include "Logger.h"

double attackTime; // NO

//Enters the Attack State - Constructor
void EnemyStateAttack::enter(){

	this->enemy->getAnimation()->changeAnimation(2, 1, 6, false, 0.6);
	this->enemy->speed = 7.0;
	attackTime = 0;

	if(enemy->life <= 0){

		enemy->vy = 0;
		enemy->changEnemyState(Enemy::EnemyStates::DEAD);

	}
}

//Exits the Attack State - Destructor
void EnemyStateAttack::exit(){
}

//Updates the Attack State
void EnemyStateAttack::update(const double deltaTime_){

	attackTime += deltaTime_;
	const double attackTotalTime = 0.6;

	/// @todo Refactor the way the enemy hurts the player.
	
	if(this->enemy->vx >= 0){

		this->enemy->vx = 0;

	}
	else{

		this->enemy->vx = -0.001; //Set this value so that the Enemy won't Flip when attacking
	
	}

	if(attackTime > attackTotalTime){
	
		if(Enemy::pVulnerable){
	
			Enemy::pLife--;
	
		}
	
		this->enemy->changEnemyState(Enemy::EnemyStates::ALERT);
	
	}
}

EnemyStateAttack::EnemyStateAttack(Enemy* const enemy_) :
	
	StateEnemy(enemy_)
{
}
