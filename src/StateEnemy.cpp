#include "StateEnemy.h"

StateEnemy::StateEnemy(Enemy* const enemy_) :
	enemy(enemy_)
{

}

StateEnemy::~StateEnemy(){
	this->enemy = nullptr;
}
