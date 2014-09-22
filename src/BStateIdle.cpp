#include "BStateIdle.h"
#include "Logger.h"

void BStateIdle::enter(){

	Log(DEBUG) << "STATE IDLE BOSS";
	this->boss->getAnimation()->changeAnimation(0, 0, 7, false, 1);

}

void BStateIdle::exit(){
}

void BStateIdle::update(const double deltaTime_){

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

		this->boss->changeState(Boss::BStates::ATTACK);

	}

}

BStateIdle::BStateIdle(Boss* const boss_) :

	StateBoss(boss_)
	
{
}
