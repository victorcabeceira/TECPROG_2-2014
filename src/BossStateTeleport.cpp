#include "BossStateTeleport.h"
#include "Game.h"
#include "Collision.h"
#include "Logger.h"

/**
* @see StateBoss::enter.
*/
void BossStateTeleport::enter(){

	// Log(DEBUG) << "STATE TELEPORT BOSS";
	this->boss->power = Game::instance().getResources().get("res/images/laser_sheet.png");
	this->boss->powerAnimation->changeWidthHeight(700, 340);
	this->boss->powerAnimation->changeAnimation(0, 0, 3, false, 0.5);
	this->boss->player->isVulnerable = true;
	this->axisOffset = 33;
	this->direction = 0;

}

/**
* @see StateBoss::exit.
*/
void BossStateTeleport::exit(){

	this->boss->powerIsActivated = false;
	this->boss->player->isVulnerable = true;
	this->boss->powerAnimation->changeAnimation(0, 0, 1, false, 0);
	this->powerCollisionWidth = 0;
	this->powerCollisionHeight = 0;
	this->teleportTime = 0.0;

}

/**
* @see StateBoss::update.
*/
void BossStateTeleport::update(const double deltaTime_){

	this->teleportTime += deltaTime_;
	
	if(this->teleportTime < this->START_TIME_TELEPORT){

		this->boss->vx =0;
		this->boss->vy =0;

	}
	else if(this->teleportTime >= this->START_TIME_TELEPORT && this->teleportTime <= this->MID_TIME_TELEPORT){

		this->boss->getAnimation()->changeAnimation(0, 0, 1, false, 0);
		this->boss->vx = 0;

		if(this->boss->player->isRight){

			this->boss->x = this->boss->player->x - 150 - 50;
			this->boss->y = this->boss->player->y;

		}
		else{

			this->boss->x = this->boss->player->x + 150 + 50;
			this->boss->y = this->boss->player->y;

		}

		this->boss->isRight = this->boss->player->isRight;
		this->playerX = this->boss->x;
		this->playerY = this->boss->y;

		if(!this->boss->isRight){

			this->boss->powerFlip = SDL_FLIP_HORIZONTAL;
			this->right = false;

		}
		else{

			this->boss->powerFlip = SDL_FLIP_NONE;
			this->right = false;

		}
	}

	else if(this->teleportTime > this->MID_TIME_TELEPORT && this->teleportTime < this->MID_END_TIME_TELEPORT){

		this->boss->x = this->playerX;
		this->boss->y = this->playerY;

		if(this->right){

			this->boss->isRight = false;
			this->direction = 0;

		}
		else{

			this->boss->isRight = true;
			this->direction = 1;

		}
	}

	if(this->teleportTime >= MID_END_TIME_TELEPORT && this->teleportTime <= MAX_TIME_TELEPORT){

		if(this->boss->powerAnimation->getCurrentFrame() == 1){

			this->powerCollisionWidth = 101;
			this->powerCollisionHeight = 30;

		}

		else if(this->boss->powerAnimation->getCurrentFrame() == 2){

			this->powerCollisionWidth = 539;
			this->powerCollisionHeight = 117;

		}
		else{

			this->powerCollisionWidth = 665;
			this->powerCollisionHeight = 262;

		}

		if(this->boss->player->isRight){

			this->boss->powerX = this->playerX;
			this->boss->powerY = this->playerY;

		}
		else{

			this->boss->powerX = this->playerX;
			this->boss->powerY = this->playerY;

		}

		if(this->teleportTime >= 4.5){

			this->boss->powerAnimation->changeAnimation(2, 0, 1, false, 0);
			this->powerCollisionWidth = 665;
			this->powerCollisionHeight = 262;

		}

		this->boss->powerIsActivated = true;

		if(Collision::rectsCollided(this->boss->player->getBoundingBox(), {(int)this->boss->powerX - this->direction * 665, 
								   (int)this->boss->powerY + this->axisOffset, this->direction * 665, 262})){

			if(this->boss->player->isVulnerable){

				this->boss->player->life--;
				this->boss->player->isVulnerable = false;

			}
		}
	}

	else if(this->teleportTime > this->MAX_TIME_TELEPORT){

		this->boss->changEnemyState(Boss::BossStates::IDLE);

	}
}

/**
* The constructor.
* @param boss_ : Reference to the Boss.
*/
BossStateTeleport::BossStateTeleport(Boss* const boss_) :

	StateBoss(boss_)

{
}
