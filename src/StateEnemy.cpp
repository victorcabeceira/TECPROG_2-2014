#include "StateEnemy.h"

	/**
	* The constructor.
	* @param enemy_ : Reference to the Enemy.
	*/

StateEnemy::StateEnemy(Enemy* const enemy_) :
	
	enemy(enemy_)

{

}

	/**
	* The destructor.
	*/
	
StateEnemy::~StateEnemy(){

	this->enemy = nullptr;

}
