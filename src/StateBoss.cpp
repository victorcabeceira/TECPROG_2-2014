#include "StateBoss.h"

// Constructor of StateBoss, set the boss.
StateBoss::StateBoss(Boss* const boss_) :
	boss(boss_)
{

}

// Destructor method, runs when the class is deallocated.
StateBoss::~StateBoss(){
	this->boss = nullptr;
}
