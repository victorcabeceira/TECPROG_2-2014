#include "BossStateAttack.h"
#include "Logger.h"
#include "Game.h"

#include <cstdlib>
#include <ctime>

void BossStateAttack::enter(){

	Log(DEBUG) << "STATE ATTACK BOSS";
	this->boss->getAnimation()->changeAnimation(0, 0, 7, false, 1);
	this->boss->sawPlayer = false;
	this->attackIndex = rand()%4;

}

void BossStateAttack::exit(){

	this->boss->canWalk = false;

}

//Update eh state of boss skills
void BossStateAttack::update(const double deltaTime_){

	((void)deltaTime_); // Unused.

	if(this->attackIndex == 3){

		this->boss->changEnemyState(Boss::BossStates::SHIELD);

	}
	else if(this->attackIndex == 0){

		this->boss->changEnemyState(Boss::BossStates::TELEPORT);

	}
	else if(this->attackIndex == 2){

		this->boss->changEnemyState(Boss::BossStates::ICEPRISION);

	}
	else if(this->attackIndex == 1){

		this->boss->changEnemyState(Boss::BossStates::MAGICPROJECTILE);

	}
	else{
	}
}

BossStateAttack::BossStateAttack(Boss* const boss_) :

	StateBoss(boss_)

{

	srand(time(nullptr));
	
}
