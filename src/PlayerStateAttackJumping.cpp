#include "PlayerStateAttackJumping.h"
#include "Logger.h"
#include "Game.h"

//Entering the Attack Jumping state
void PlayerStateAttackJumping::enter(){

   	this->box.x = 58;
    this->box.y = 72;
    this->box.w = 130;
    this->box.h = 145;

    this->player->getAnimation()->changeAnimation(3, 9, 7, false, 0.4);
}

//Exiting the Attack Jumping state
void PlayerStateAttackJumping::exit(){
	
	std::string debug_exit ("EXIT STATE ATTACK JUMPING");

	Log(DEBUG) << debug_exit;

	this->player->canAttack = true;

}

//Handles the Input
void PlayerStateAttackJumping::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
	
	std::string debug_handle ("STATE ATTACK JUMPING");

	Log(DEBUG) << debug_handle;

	if(this->player->getAnimation()->getCurrentFrame() == 7){
		
		this->player->changEnemyState(Player::PlayerStates::AERIAL);
	
	}
	// Gravity
	this->player->applyGravity();

	// Move (while on air)
    this->player->move(keyStates_[GameKeys::LEFT], keyStates_[GameKeys::RIGHT]);
}

PlayerStateAttackJumping::PlayerStateAttackJumping(Player* const player_) :
	
	StatePlayer(player_)
{

}
