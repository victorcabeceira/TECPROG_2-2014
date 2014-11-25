#include "PlayerStateAerial.h"
#include "Logger.h"
#include "Game.h"

//Entering the Aerial State
void PlayerStateAerial::enter(){
    
    this->box.x = 58;
    this->box.y = 72;
    this->box.w = 130;
    this->box.h = 145;

	this->player->getAnimation()->changeAnimation(4, 3, 14, false, 1.4);
	this->player->isGrounded = false;

    std::string soundEffect ("res/audio/FX_NADINE/WOOSH_NADINE_02.wav");

    Game::instance().getAudioHandler().addSoundEffect(soundEffect);

}

//Exiting the Aerial State
void PlayerStateAerial::exit(){
    
    this->player->isClimbing = false;

}

//Handles the Input
void PlayerStateAerial::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	// Idle
    if(this->player->isGrounded){
    	
        this->player->changEnemyState(Player::PlayerStates::IDLE);
    	return;
    
    }

    if(keyStates_[GameKeys::LATTACK]){
      
        this->player->changEnemyState(Player::PlayerStates::ATTACKJUMPING);
        return;
    
    }

	// Gravity
	this->player->applyGravity();

	// Move (while on air)
    this->player->move(keyStates_[GameKeys::LEFT], keyStates_[GameKeys::RIGHT]);
}

PlayerStateAerial::PlayerStateAerial(Player* const player_) :
	
    StatePlayer(player_)

{    
}