#include "PlayerStateMovingCrouch.h"
#include "Logger.h"

void PlayerStateMovingCrouch::enter(){
	
	this->box.x = (int)this->player->getWidth() / 4 - 33;
    this->box.w = (int)this->player->getWidth() / 1.7;
	this->box.y = (int)this->player->getHeight() / 2;
	this->box.h = (int)this->player->getHeight() / 2;

	this->player->getAnimation()->changeAnimation(3, 10, 6, true, 1);
	this->player->isGrounded = true;
	this->player->maxSpeed /= 2;
	this->player->speed = 15;

}

void PlayerStateMovingCrouch::exit(){
	
	this->player->maxSpeed *= 2;
	this->player->speed = 20;

}

void PlayerStateMovingCrouch::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	// Not crouching, goes to Idle.
	if(!keyStates_[GameKeys::CROUCH]){
		
		this->player->changeState(Player::PStates::IDLE);
		return;
	
	}

	this->player->slowVx();

	// Stops moving, goes to Crouch.
    if(!keyStates_[GameKeys::LEFT] && !keyStates_[GameKeys::RIGHT]){
     
        this->player->changeState(Player::PStates::CROUCHING);
        return;
    
    }

	// Jump
	if(keyStates_[GameKeys::SPACE]){
		
		this->player->jump();
		this->player->isGrounded = false;
		return;
	
	}

	this->player->move(keyStates_[GameKeys::LEFT], keyStates_[GameKeys::RIGHT]);

	if(keyStates_[GameKeys::ROLL]){
		
		this->player->changeState(Player::PStates::ROLLING);
		return;

	}

}

PlayerStateMovingCrouch::PlayerStateMovingCrouch(Player* const player_) :

	StatePlayer(player_)

{
	
}