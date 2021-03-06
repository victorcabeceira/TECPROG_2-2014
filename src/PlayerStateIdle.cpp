#include "PlayerStateIdle.h"
#include "Logger.h"
#include "Game.h"

#define THROW_STRENGTH 30
#define THROW_DISTANCE 400

void PlayerStateIdle::enter(){
	
	this->box.x = 58;
	this->box.y = 72;
	this->box.w = 130;
	this->box.h = 160;

	// this->box.x = (int)this->player->getWidth() / 4 - 33;
	// this->box.y = (int)this->player->getHeight() / 3.5;
	// this->box.w = (int)this->player->getWidth() / 1.7;
	// this->box.h = (int)this->player->getHeight() / 3.5;

	this->player->getAnimation()->changeAnimation(0, 0, 26, false, 2.6);
	this->player->isGrounded = true;
}

void PlayerStateIdle::exit(){

}

void PlayerStateIdle::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	// Aerial
	if(!this->player->isGrounded){
		
		this->player->changEnemyState(Player::PlayerStates::AERIAL);
		return;
	
	}

	this->player->slowVx();

	// Jump
	if(keyStates_[GameKeys::SPACE]){
		
		this->player->jump();
		this->player->isGrounded = false;
		return;
	
	}

	// Attack
	if(keyStates_[GameKeys::LATTACK]){
		
		this->player->changEnemyState(Player::PlayerStates::ATTACK);
		return;
	
	}

    if(keyStates_[GameKeys::ACTION]){
    	
    	// Game::instance().getAudioHandler().addSoundEffect("res/audio/FX_NADINE/FX_AAAAAHH.wav");
        this->player->usePotion(THROW_STRENGTH, THROW_DISTANCE);
        return;
    
    }

	// // Crouch
	// if(keyStates_[GameKeys::CROUCH]){
	// 	this->player->changEnemyState(Player::PlayerStates::CROUCHING);
	// 	return;
	// }

	// Move
	if(keyStates_[GameKeys::LEFT] || keyStates_[GameKeys::RIGHT]){
		
		this->player->changEnemyState(Player::PlayerStates::MOVING);
		return;
	
	}

	// Roll
	if(keyStates_[GameKeys::ROLL]){
		
		this->player->changEnemyState(Player::PlayerStates::ROLLING);
		return;
	}

	// Aim
	if(keyStates_[GameKeys::AIM]){
		
		this->player->changEnemyState(Player::PlayerStates::AIMING);
		return;
	
	}

}

PlayerStateIdle::PlayerStateIdle(Player* const player_) :

	StatePlayer(player_)

{

}
