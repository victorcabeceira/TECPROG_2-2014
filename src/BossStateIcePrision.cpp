#include "BossStateIcePrision.h"
#include "Logger.h"
#include "Sprite.h"
#include "Game.h"
#include "Collision.h"

void BossStateIcePrision::enter(){

	// Log(DEBUG) << "STATE ICE PRISION BOSS";
	this->boss->power = Game::instance().getResources().get("res/images/ice_prision.png");
	this->boss->powerAnimation->changeWidthHeight(340,1020);
	this->boss->powerAnimation->changeAnimation(0, 0, 2, false, 0.5);
	this->boss->vx = 0;
	this->boss->vy = 0;
	this->boss->powerIsActivated = true;
	this->boss->powerX = this->boss->player->x - 30; 
	this->boss->powerY = this->boss->player->y - 750;
	this->boss->powerFlip = SDL_FLIP_NONE;
	this->prisionTime = 0.0;

}

void BossStateIcePrision::exit(){

	this->boss->powerIsActivated = false;
	this->boss->player->isVulnerable = true;
	this->boss->powerAnimation->changeAnimation(0, 0, 1, false, 0);
	this->prisionTime = 0.0;
	this->boss->player->canMove = true;

}

void BossStateIcePrision::update(const double deltaTime_){

	this->prisionTime += deltaTime_;
	if(this->prisionTime > 1){

		this->boss->powerAnimation->changeAnimation(2, 0, 1, false, 0);

		if(Collision::rectsCollided(this->boss->player->getBoundingBox(),  {(int)this->boss->powerX, 
								   (int)this->boss->powerY, 340,1020})){

			if(this->boss->player->isVulnerable){

				this->boss->player->canMove = false;
				this->boss->player->isVulnerable = false;
				this->boss->player->vx = 0;
				this->boss->player->vy = 0;
				this->boss->player->getAnimation()->changeAnimation(4, 8, 1, false, 0);

			}
		}
	}

	if(this->prisionTime > 4){

		this->boss->changEnemyState(Boss::BossStates::IDLE);

	}
}

BossStateIcePrision::BossStateIcePrision(Boss* const boss_) :

	StateBoss(boss_)
	
{
}
