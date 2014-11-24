#include "PlayerStateRolling.h"
#include "Logger.h"
#include "Game.h"

	/**
	* @see StatePlayer::enter
	*/

void PlayerStateRolling::enter(){
	
	this->box.x = 58;
	this->box.y = 72;
	this->box.w = 140;
	this->box.h = 160;

	this->player->getAnimation()->changeAnimation(6, 4, 9, true, 0.6);
	this->player->roll();

	Game::instance().getAudioHandler().addSoundEffect("res/audio/FX_NADINE/ROLLING_NADINE_01.wav");

}

	/**
	* @see StatePlayer::exit
	*/

void PlayerStateRolling::exit(){

}

	/**
	* @see StatePlayer::handleInput
	*/
	
void PlayerStateRolling::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	// Aerial
	if(!this->player->isGrounded){
		
		this->player->changEnemyState(Player::PlayerStates::AERIAL);
		return;
	
	}

    this->player->slowVx();

	// Jump
	if(keyStates_[GameKeys::SPACE] && this->player->isGrounded){
		
		this->player->jump();
		this->player->changEnemyState(Player::PlayerStates::AERIAL);
		return;
	
	}

	// Idle
    if(this->player->vx < 1.0 && this->player->vx > (-1.0)){
    
        this->player->changEnemyState(Player::PlayerStates::IDLE);
        return;
    
    }
}

	/**
	* The constructor.
	* @param player_ : Reference to the player.
	*/

PlayerStateRolling::PlayerStateRolling(Player* const player_) :
    
    StatePlayer(player_)
{

}