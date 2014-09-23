#include "PlayerStateRolling.h"
#include "Logger.h"
#include "Game.h"

void PlayerStateRolling::enter(){
	
	this->box.x = 58;
	this->box.y = 72;
	this->box.w = 140;
	this->box.h = 160;

	this->player->getAnimation()->changeAnimation(6, 4, 9, true, 0.6);
	this->player->roll();

	Game::instance().getAudioHandler().addSoundEffect("res/audio/FX_NADINE/ROLLING_NADINE_01.wav");

}

void PlayerStateRolling::exit(){

}

void PlayerStateRolling::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	// Aerial
	if(!this->player->isGrounded){
		
		this->player->changEnemyState(Player::PStates::AERIAL);
		return;
	
	}

    this->player->slowVx();

	// Jump
	if(keyStates_[GameKeys::SPACE] && this->player->isGrounded){
		
		this->player->jump();
		this->player->changEnemyState(Player::PStates::AERIAL);
		return;
	
	}

	// Idle
    if(this->player->vx < 1.0 && this->player->vx > (-1.0)){
    
        this->player->changEnemyState(Player::PStates::IDLE);
        return;
    
    }
}

PlayerStateRolling::PlayerStateRolling(Player* const player_) :
    
    StatePlayer(player_)
{

}