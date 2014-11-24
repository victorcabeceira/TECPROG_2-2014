#include "StateBoss.h"

	/**
	* The constructor.
	* @param boss_ : Reference to the Boss.
	*/

StateBoss::StateBoss(Boss* const boss_) :

	boss(boss_)

{

}

	/**
	* The destructor.
	*/
	
StateBoss::~StateBoss(){
	
	this->boss = nullptr;

}
