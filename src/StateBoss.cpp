#include "StateBoss.h"

StateBoss::StateBoss(Boss* const boss_) :
	boss(boss_)
{

}

StateBoss::~StateBoss(){
	this->boss = nullptr;
}
