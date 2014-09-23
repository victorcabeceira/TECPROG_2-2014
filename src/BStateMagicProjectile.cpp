#include "BossStateMagicProjectile.h"
#include "Logger.h"
#include "Sprite.h"
#include "Game.h"
#include "Collision.h"
#include <cmath>

double projectileTime = 0.0;
double mpX = 0;
double mpY = 0;
double hypotenuse = 0;

void BossStateMagicProjectile::enter(){

	// Log(DEBUG) << "STATE MAGIC PROJECTILE BOSS";
	this->boss->power = Game::instance().getResources().get("res/images/projectile.png");
	this->boss->powerAnimation->changeWidthHeight(50,50);
	this->boss->powerAnimation->changeAnimation(0, 0, 4, false, 0.5);
	this->boss->vx = 0;
	this->boss->vy = 0;
	this->boss->powerX = this->boss->x + 50;
	this->boss->powerY = this->boss->y + 150;

	mpX = this->boss->player->getBoundingBox().x + 50 - this->boss->getBoundingBox().x;
	mpY = this->boss->player->getBoundingBox().y + 50 - this->boss->getBoundingBox().y;
	hypotenuse = sqrt((mpX*mpX)+(mpY*mpY));
	hypotenuse = (hypotenuse==0) ? 1 : hypotenuse;
	mpX /= hypotenuse;
	mpY /= hypotenuse;

}

void BossStateMagicProjectile::exit(){

	this->boss->powerIsActivated = false;
	projectileTime = 0.0;
	mpX = 0;
	mpY = 0;
	hypotenuse = 0;
	this->boss->powerAnimation->changeWidthHeight(50,50);

}

void BossStateMagicProjectile::update(const double deltaTime_){

	projectileTime += deltaTime_;
	this->boss->powerX += mpX * 15;
	this->boss->powerY += mpY * 15;
	this->boss->powerIsActivated = true;

	if(Collision::rectsCollided(this->boss->player->getBoundingBox(), {(int)this->boss->powerX, 
							   (int)this->boss->powerY, 50, 50})){

			this->boss->player->life--;
			this->boss->changeState(Boss::BossStates::IDLE);

	}

	if(projectileTime>3){

		this->boss->changeState(Boss::BossStates::IDLE);

	}
}

BossStateMagicProjectile::BossStateMagicProjectile(Boss* const boss_) :

	StateBoss(boss_)

{
}
