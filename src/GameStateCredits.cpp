#include "GamEnemyStateCredits.h"
#include "LuaScript.h"
#include "Logger.h"
#include "Game.h"

#include <string>

GamEnemyStateCredits::GamEnemyStateCredits() :

	creditsImage(nullptr),
	creditsHeightSize(600),
	creditsChangeSpeed(2),
	creditsClip{0, 0, 0, this->creditsHeightSize}

{
}

GamEnemyStateCredits::~GamEnemyStateCredits(){
}

void GamEnemyStateCredits::update(const double deltaTime_){

	(void(deltaTime_)); //unused
	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

	if(keyStates[GameKeys::LATTACK] == true){

		Game::instance().setState(Game::GStates::MENU);

	}
}

void GamEnemyStateCredits::load(){

	Log(DEBUG) << "Loading credits...";

	LuaScript luaCredits("lua/Credits.lua");
	const std::string pathCredits = luaCredits.unlua_get<std::string>("credits.images.dummy");
	
    this->creditsImage = Game::instance().getResources().get(pathCredits);
    this->creditsClip.w = this->creditsImage->getWidth();

}

void GamEnemyStateCredits::unload(){

	Log(DEBUG) << "\tUnloading credits...";
	this->creditsClip.y = 0;
	cleanEntities();

}

void GamEnemyStateCredits::render(){

	if(this->creditsImage != nullptr){

		if(this->creditsClip.y < (int)this->creditsImage->getHeight() - this->creditsHeightSize){

			this->creditsClip.y += this->creditsChangeSpeed;

		}

		this->creditsImage->render(0, 0, &this->creditsClip, true);

	}
	else{

		Log(WARN) << "No image set for the options screen!";

	}
}
