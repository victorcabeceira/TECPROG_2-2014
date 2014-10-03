#include "BossStateIdle.h"
#include "Logger.h"

void BossStateIdle::enter(){

	Log(DEBUG) << "STATE IDLE BOSS";
	this->boss->getAnimation()->changeAnimation(0, 0, 7, false, 1);

}

void BossStateIdle::exit(){
}

void BossStateIdle::update(const double deltaTime_){

	((void)deltaTime_); // Unused.

	if(this->boss->isRight && this->boss->x > 1960){

		this->boss->isRight = false;

	}
	else if(!this->boss->isRight && this->boss->x < 300){

		this->boss->isRight = true;

	}
	
	if(this->boss->isRight){

		this->boss->move(false, true);

	}
	else{

		this->boss->move(true, false);

	}

	if(this->boss->sawPlayer){

		this->boss->changEnemyState(Boss::BossStates::ATTACK);

	}

}

BossStateIdle::BossStateIdle(Boss* const boss_) :

	StateBoss(boss_)
	
{
}
