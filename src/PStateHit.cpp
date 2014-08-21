#include "PStateHit.h"
#include "Logger.h"

void PStateHit::enter(){
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

void PStateHit::exit(){

	if(this->player->isRight)
		this->player->vx = 0.0;
	else
		this->player->vx = -0.001;
}

void PStateHit::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
	((void) keyStates_); // Unused.
}

PStateHit::PStateHit(Player* const player_) :
	StatePlayer(player_)
{

}
