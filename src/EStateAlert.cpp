#include "EnemyStateAlert.h"
#include "Logger.h"

void EnemyStateAlert::enter(){

	this->enemy->getAnimation()->changeAnimation(1, 0, 9, false, 0.9);
	this->enemy->speed = 6.5;

	if(enemy->life <= 0){

		enemy->vy = 0;
		enemy->changEnemyState(Enemy::EnemyStates::DEAD);

	}
}

void EnemyStateAlert::exit(){
}

void EnemyStateAlert::update(const double deltaTime_){

	((void)deltaTime_); // Unused.
	
	// Aerial
	if(!this->enemy->isGrounded){

		this->enemy->changEnemyState(Enemy::EnemyStates::AERIAL);
		return;

	}

	if(this->enemy->x - Enemy::px < 0.0){

		this->enemy->vx += this->enemy->speed;

	}
	else{

		this->enemy->vx -= this->enemy->speed;

	}

	if(abs(this->enemy->x - Enemy::px) < 100){

		if(abs(this->enemy->y - Enemy::py) < 200){

			this->enemy->changEnemyState(Enemy::EnemyStates::ATTACK);

		}
	}

	if(!(abs(this->enemy->x - Enemy::px) < Enemy::alertRange*2 && abs(this->enemy->y - Enemy::py) < Enemy::alertRange)){

		this->enemy->changEnemyState(Enemy::EnemyStates::PATROLLING);
		return;
	
	}	
}

EnemyStateAlert::EnemyStateAlert(Enemy* const enemy_) :

	StateEnemy(enemy_)
{
}
