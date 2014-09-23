#include "EnemyStateCurious.h"
#include "Logger.h"

#define MAX_CURIOUS_TIME 4.666

void EnemyStateCurious::enter(){

	this->enemy->getAnimation()->changeAnimation(1, 0, 9, false, 1.2);
	this->enemy->speed = 5.0;

	if(enemy->life <= 0){

		enemy->vy = 0;
		enemy->changEnemyState(Enemy::EnemyStates::DEAD);

	}
}

void EnemyStateCurious::exit(){
}

void EnemyStateCurious::update(const double deltaTime_){

	this->timeElapsed += deltaTime_;

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

	// 
	if(abs(this->enemy->x - Enemy::px) < Enemy::alertRange && abs(this->enemy->y - Enemy::py) < Enemy::alertRange){
	
		this->enemy->changEnemyState(Enemy::EnemyStates::ALERT);
		return;
	
	}

	if(timeElapsed >= MAX_CURIOUS_TIME){
	
		this->enemy->changEnemyState(Enemy::EnemyStates::PATROLLING);
		return;
	
	}
}

EnemyStateCurious::EnemyStateCurious(Enemy* const enemy_) :
	
	StateEnemy(enemy_),
	timeElapsed(0.0)
{
}
