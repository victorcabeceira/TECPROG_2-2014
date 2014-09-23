#include "PStateAttackMoving.h"
#include "Logger.h"

void PStateAttackMoving::enter(){
	
	this->box.x = 58;
	this->box.y = 72;
	this->box.w = 130;
	this->box.h = 160;

	this->player->getAnimation()->changeAnimation(5, 8, 9, false, 0.7);

}

void PStateAttackMoving::exit(){
	
	this->player->canAttack = true;

}

void PStateAttackMoving::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
	
	this->player->move(keyStates_[GameKeys::LEFT], keyStates_[GameKeys::RIGHT]);
	
	if(this->player->getAnimation()->getCurrentFrame() == 9){
		
		this->player->changEnemyState(Player::PStates::MOVING);
	
	}
}

PStateAttackMoving::PStateAttackMoving(Player* const player_) :
	
	StatePlayer(player_)
{

}