#include "PlayerStateHit.h"
#include "Logger.h"
// Enter on state hit
void PlayerStateHit::enter(){
	
	Log(DEBUG) << "STATE ATTACK JUMPING";
	
   	this->box.x = 58;
    this->box.y = 72;
    this->box.w = 130;
    this->box.h = 145;

	this->player->getAnimation()->changeAnimation(4, 8, 1, false, 0);

	int direction = 1;
	if(this->player->isRight){
		
		direction = -1;
	}
	
	this->player->vy = -130;
	this->player->vx = 5000 * direction;
}
//Exiting of state hit
void PlayerStateHit::exit(){

	if(this->player->isRight){
		
		this->player->vx = 0.0;
	}
	else{
		
		this->player->vx = -0.001;
	}	
}

void PlayerStateHit::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
	
	((void) keyStates_); // Unused.

}

PlayerStateHit::PlayerStateHit(Player* const player_) :
	
	StatePlayer(player_)

{

}
