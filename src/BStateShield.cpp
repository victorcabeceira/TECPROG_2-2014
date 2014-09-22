#include "BStateShield.h"
#include "Logger.h"

void BStateShield::enter(){

	Log(DEBUG) << "STATE SHIELD BOSS";
	this->boss->getAnimation()->changeAnimation(0, 0, 1, false, 0);
	this->boss->hasShield = true;

}

void BStateShield::exit(){
}

void BStateShield::update(const double deltaTime_){

	((void)deltaTime_); // Unused.

	this->boss->changeState(Boss::BStates::IDLE);

}

BStateShield::BStateShield(Boss* const boss_) :

	StateBoss(boss_)

{
}
