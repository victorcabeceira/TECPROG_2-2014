#include "BossStateShield.h"
#include "Logger.h"

void BossStateShield::enter(){

	Log(DEBUG) << "STATE SHIELD BOSS";
	this->boss->getAnimation()->changeAnimation(0, 0, 1, false, 0);
	this->boss->hasShield = true;

}

void BossStateShield::exit(){
}

void BossStateShield::update(const double deltaTime_){

	((void)deltaTime_); // Unused. Variable necessary for the update state.

	this->boss->changEnemyState(Boss::BossStates::IDLE);

}

BossStateShield::BossStateShield(Boss* const boss_) :

	StateBoss(boss_)

{
}