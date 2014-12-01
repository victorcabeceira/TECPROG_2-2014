#include "EnemyStateDead.h"
#include "Logger.h"

double deadTime;

//Enters the Dead State - Constructor
void EnemyStateDead::enter(){

	this->enemy->life = 0;
	this->enemy->setDead(true);
	this->enemy->getAnimation()->changeAnimation(1, 1, 1, false, 0);

}

//Exits the Dead State - Destructor
void EnemyStateDead::exit(){
}

//Updates the Dead State
void EnemyStateDead::update(const double deltaTime_){
	
	deadTime += deltaTime_;
	
	if(deadTime >= 2){
	
		this->enemy->setDead(true);
	
	}
	
	this->enemy->vx = 0;

}

EnemyStateDead::EnemyStateDead(Enemy* const enemy_) :

	StateEnemy(enemy_)
{
}
