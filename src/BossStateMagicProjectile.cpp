#include "BossStateMagicProjectile.h"
#include "Logger.h"
#include "Sprite.h"
#include "Game.h"
#include "Collision.h"
#include <cmath>


void BossStateMagicProjectile::enter(){

	// Log(DEBUG) << "STATE MAGIC PROJECTILE BOSS";
	this->boss->power = Game::instance().getResources().get("res/images/projectile.png");
	this->boss->powerAnimation->changeWidthHeight(50,50);
	this->boss->powerAnimation->changeAnimation(0, 0, 4, false, 0.5);
	this->boss->vx = 0;
	this->boss->vy = 0;
	this->boss->powerX = this->boss->x + 50;
	this->boss->powerY = this->boss->y + 150;

	this->magicProjectileX = this->boss->player->getBoundingBox().x + 50 - this->boss->getBoundingBox().x;
	this->magicProjectileY = this->boss->player->getBoundingBox().y + 50 - this->boss->getBoundingBox().y;
	this->distanceBossPlayer = sqrt((this->magicProjectileX*this->magicProjectileX)+(this->magicProjectileY*this->magicProjectileY));
	this->distanceBossPlayer = (this->distanceBossPlayer==0) ? 1 : this->distanceBossPlayer;
	this->magicProjectileX /= this->distanceBossPlayer;
	this->magicProjectileY /= this->distanceBossPlayer;

}

void BossStateMagicProjectile::exit(){

	this->boss->powerIsActivated = false;
	this->projectileTime = 0.0;
	this->magicProjectileX = 0;
	this->magicProjectileY = 0;
	this->distanceBossPlayer = 0;
	this->boss->powerAnimation->changeWidthHeight(50,50);

}

void BossStateMagicProjectile::update(const double deltaTime_){

	this->projectileTime += deltaTime_;
	this->boss->powerX += this->magicProjectileX * 15;
	this->boss->powerY += this->magicProjectileY * 15;
	this->boss->powerIsActivated = true;

	if(Collision::rectsCollided(this->boss->player->getBoundingBox(), {(int)this->boss->powerX, 
							   (int)this->boss->powerY, 50, 50})){

			this->boss->player->life--;
			this->boss->changEnemyState(Boss::BossStates::IDLE);

	}

	if(this->projectileTime>3){

		this->boss->changEnemyState(Boss::BossStates::IDLE);

	}
}

BossStateMagicProjectile::BossStateMagicProjectile(Boss* const boss_) :

	StateBoss(boss_)

{
}
