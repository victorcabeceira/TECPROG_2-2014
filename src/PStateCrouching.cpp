#include "PStateCrouching.h"
#include "Logger.h"

void PStateCrouching::enter(){

	this->box.x = (int)this->player->getWidth() / 4 - 33;
    this->box.w = (int)this->player->getWidth() / 1.7;
	this->box.y = (int)this->player->getHeight() / 2;
	this->box.h = (int)this->player->getHeight() / 2;

	this->player->getAnimation()->changeAnimation(10,13,2,false,0.3);
	this->player->isGrounded = true;
}

void PStateCrouching::exit(){
	this->player->getAnimation()->changeAnimation(1,14,2,false,0.3);
}

void PStateCrouching::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
	this->player->getAnimation()->changeAnimation(8,9,1,false,0);

	if(!keyStates_[GameKeys::CROUCH]){
		this->player->changeState(Player::PStates::IDLE);
		return;
	}

	this->player->slowVx();

	// Jump
	if(keyStates_[GameKeys::SPACE]){
		this->player->jump();
		this->player->isGrounded = false;
		return;
	}

	if(keyStates_[GameKeys::LEFT] || keyStates_[GameKeys::RIGHT]){
		this->player->changeState(Player::PStates::MOVINGCROUCH);
		return;
	}

	if(keyStates_[GameKeys::ROLL]){
		this->player->changeState(Player::PStates::ROLLING);
		return;
	}

}

PStateCrouching::PStateCrouching(Player* const player_) :
	StatePlayer(player_)
{
	
}
