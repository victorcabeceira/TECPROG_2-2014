#include "PlayerStateAiming.h"
#include "Logger.h"
#include "Game.h"
#define RIGHTD 1
#define LEFTD -1
#define NONED 0

#define THROW_STRENGTH 30

#define MAX_DISTANCE 300
#define MIN_DISTANCE 50

//Entering the Aiming State
void PlayerStateAiming::enter(){

	this->box.x = 58;
	this->box.y = 72;
	this->box.w = 140;
	this->box.h = 160;

	this->player->crosshair->activated = true;

	if(this->player->isRight){

		this->player->crosshair->x = this->player->getBoundingBox().x + this->player->getBoundingBox().w;

	}
	else{

		this->player->crosshair->x = this->player->getBoundingBox().x - this->player->crosshair->getWidth();

	}

	this->player->crosshair->y = this->player->y + this->player->getHeight() - this->player->crosshair->getHeight();

}

//Exiting the Aiming State
void PlayerStateAiming::exit(){

	this->player->crosshair->activated = false;

}

//Handles the Input
void PlayerStateAiming::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	this->player->crosshair->render(0.0, 0.0);

	if(!keyStates_[GameKeys::AIM]){

		this->player->changEnemyState(Player::PlayerStates::IDLE);
		return;

	}

	if(keyStates_[GameKeys::ACTION]){

		if(this->player->currentItem == Player::PItems::POTION){
			this->player->usePotion(THROW_STRENGTH, absoluteCrosshairPlayerDistance());
			return;
		}
	}
	
	if(keyStates_[GameKeys::LEFT]){
		
		if(this->player->isRight){

			if((this->player->crosshair->x > (this->player->getBoundingBox().x + this->player->getBoundingBox().w))){

				this->player->aim(this->player->crosshair, LEFTD);

			}
				
		}
		
		else if (absoluteCrosshairPlayerDistance() < MAX_DISTANCE) {

			this->player->aim(this->player->crosshair, LEFTD);

		}

		return;
	}

	else if(keyStates_[GameKeys::RIGHT]){

		if(!this->player->isRight){

			if((this->player->crosshair->x < (this->player->getBoundingBox().x - this->player->crosshair->getWidth()))){

				this->player->aim(this->player->crosshair, RIGHTD);

			}	
		}

		else if (absoluteCrosshairPlayerDistance() < MAX_DISTANCE) {

			this->player->aim(this->player->crosshair, RIGHTD);

		}

		return;

	}

	else{

		this->player->aim(this->player->crosshair, NONED);
		return;

	}
}

PlayerStateAiming::PlayerStateAiming(Player* const player_) :

	StatePlayer(player_)
{

}

//The absolute position of the crosshair of the player
int PlayerStateAiming::absoluteCrosshairPlayerDistance(){

	int distance = 0;

	if(this->player->isRight){

		distance = (int) this->player->crosshair->x - this->player->getBoundingBox().x - this->player->getBoundingBox().w;

	}

	else{

		distance = (int) this->player->getBoundingBox().x - this->player->crosshair->x - this->player->crosshair->getWidth();

	}

	if(distance < MIN_DISTANCE){

		distance = MIN_DISTANCE;

	}

	return distance;
}
