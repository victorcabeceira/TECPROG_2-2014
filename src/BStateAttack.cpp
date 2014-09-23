#include "BossStateAttack.h"
#include "Logger.h"
#include "Game.h"

#include <cstdlib>
#include <ctime>

int attackIndex = 0;

void BossStateAttack::enter(){

	Log(DEBUG) << "STATE ATTACK BOSS";
	this->boss->getAnimation()->changeAnimation(0, 0, 7, false, 1);
	this->boss->sawPlayer = false;
	attackIndex = rand()%4;

}

void BossStateAttack::exit(){

	this->boss->canWalk = false;

}

//Update eh state of boss skills
void BossStateAttack::update(const double deltaTime_){

	((void)deltaTime_); // Unused.

	if(attackIndex == 3){

		this->boss->changeState(Boss::BossStates::SHIELD);

	}
	else if(attackIndex == 0){

		this->boss->changeState(Boss::BossStates::TELEPORT);

	}
	else if(attackIndex == 2){

		this->boss->changeState(Boss::BossStates::ICEPRISION);

	}
	else if(attackIndex == 1){

		this->boss->changeState(Boss::BossStates::MAGICPROJECTILE);

	}
	else{
	}
}

BossStateAttack::BossStateAttack(Boss* const boss_) :

	StateBoss(boss_)

{

	srand(time(nullptr));
	
}
