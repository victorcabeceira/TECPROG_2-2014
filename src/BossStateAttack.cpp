#include "BossStateAttack.h"
#include "Logger.h"
#include "Game.h"

#include <cstdlib>
#include <ctime>

// Initialize the boss state attack.
void BossStateAttack::enter(){

	Log(DEBUG) << "STATE ATTACK BOSS";

	// Change animation and choose randomcally the next attack.
	this->boss->getAnimation()->changeAnimation(0, 0, 7, false, 1);
	this->boss->sawPlayer = false;
	this->attackIndex = rand()%this->RANDOM_ATTACK;
	
}

// Exit from the boss state attack.
void BossStateAttack::exit(){

	this->boss->canWalk = false;

}

//Update the state of boss skills
void BossStateAttack::update(const double deltaTime_){

	// Prevent warning of unused.
	((void)deltaTime_);

	// Acording with the chose attack, change the state.
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

// Constructor, creates the boss state attack.
BossStateAttack::BossStateAttack(Boss* const boss_) :

	StateBoss(boss_)

{

	srand(time(nullptr));
	
}
