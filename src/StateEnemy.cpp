#include "StateEnemy.h"

// Constructor of StateEnemy, set the enemy.
StateEnemy::StateEnemy(Enemy* const enemy_) :
	enemy(enemy_)
{

}

// Destructor method, runs when the class is deallocated.
StateEnemy::~StateEnemy(){
	this->enemy = nullptr;
}
