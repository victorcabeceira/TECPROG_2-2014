#include "GamEnemyStateTransition.h"
#include "Game.h"
#include "Logger.h"

GamEnemyStateTransition::GamEnemyStateTransition() :

	passedTime(0.0),
	lifeTime(0.0),
	loading(nullptr),
	point(nullptr)

{
}

GamEnemyStateTransition::~GamEnemyStateTransition(){
}

void GamEnemyStateTransition::load(){

	Log(DEBUG) << "Loading transition...";

	this->loading = Game::instance().getResources().get("res/images/loading.png");
	this->point = Game::instance().getResources().get("res/images/point.png");

	if(this->loading == nullptr){

		Log(WARN) << "Unable to load transition loading image.";

	}

	if(this->point == nullptr){

		Log(WARN) << "Unable to load transition point image.";

	}

	this->lifeTime = 3.0;

}

void GamEnemyStateTransition::unload(){

	Log(DEBUG) << "\tUnloading transition...";

	this->passedTime = 0.0;
	this->lifeTime = 0.0;

	cleanEntities();

}

void GamEnemyStateTransition::update(const double deltaTime_){

	this->passedTime += deltaTime_;

	if(this->passedTime >= this->lifeTime){

		Game::instance().setState(Game::instance().transitionTo);

	}

}

void GamEnemyStateTransition::render(){

	this->loading->render(0, 0, nullptr, true);

	if(this->passedTime > 0.83){

		this->point->render(670, 235);

	}

	if(this->passedTime > 1.66){

		this->point->render(770, 235);

	}

	if(this->passedTime > 2.5){

		this->point->render(870, 235);

	}

}
