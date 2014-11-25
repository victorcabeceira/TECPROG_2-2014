#include "PlayerStateAttack.h"
#include "Logger.h"
#include "Game.h"

//Entering the Attack State
void PlayerStateAttack::enter(){
	
	this->box.x = 58;
	this->box.y = 75;
	this->box.w = 140;
	this->box.h = 160;

	this->player->getAnimation()->changeAnimation(1, 7, 14, false, 0.466);

	std::string soundEffect ("res/audio/FX_NADINE/WOOSH_NADINE_02.wav");

	Game::instance().getAudioHandler().addSoundEffect(soundEffect);
}

//Exiting the Attack state
void PlayerStateAttack::exit(){

	this->player->canAttack = true;

}

//Handles the Input
void PlayerStateAttack::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
	
	((void)keyStates_); // Unused.

	if(this->player->getAnimation()->getCurrentFrame() == 14){
		
		this->player->changEnemyState(Player::PlayerStates::IDLE);
	
	}
}

//Instance Player
PlayerStateAttack::PlayerStateAttack(Player* const player_) :
	
	StatePlayer(player_)

{

}
