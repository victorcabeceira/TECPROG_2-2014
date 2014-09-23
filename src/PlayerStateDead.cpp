#include "PlayerStateDead.h"
#include "Logger.h"
#include "Game.h"

void PlayerStateDead::enter(){
	
	Log(DEBUG) << "STATE DEAD";
	
	this->box.x = 58;
	this->box.y = 72;
	this->box.w = 130;
	this->box.h = 160;

	this->player->getAnimation()->changeAnimation(8, 4, 1, false, 0);
	this->player->isGrounded = false;

}

void PlayerStateDead::exit(){

}

void PlayerStateDead::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
	
	((void) keyStates_); // Unused.
	this->player->applyGravity();

}

PlayerStateDead::PlayerStateDead(Player* const player_) :
	
	StatePlayer(player_)

{

}
