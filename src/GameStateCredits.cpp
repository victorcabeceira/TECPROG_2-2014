#include "GameStateCredits.h"
#include "LuaScript.h"
#include "Logger.h"
#include "Game.h"

#include <string>

/**
* The state for the initial menu screen.
* Game state that will contain the game over screen.
*/
GameStateCredits::GameStateCredits() :

	creditsImage(nullptr),
	creditsHeightSize(600),
	creditsChangeSpeed(2),
	creditsClip{0, 0, 0, this->creditsHeightSize}

{
}

GameStateCredits::~GameStateCredits(){
}
/**
* Updates the objects within the StateGame.
* @param deltaTime_ : Delta time. Time elapsed between one frame and the other.
*/
void GameStateCredits::update(const double deltaTime_){

	(void(deltaTime_)); //unused
	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

	if(keyStates[GameKeys::LATTACK] == true){

		Game::instance().setState(Game::GameStates::MENU);

	}
}
/**
* Loads the level.
* From the menu.lua script, loads all the necessary objects.
*/
void GameStateCredits::load(){

	Log(DEBUG) << "Loading credits...";

	LuaScript luaCredits("lua/Credits.lua");
	const std::string pathCredits = luaCredits.unlua_get<std::string>("credits.images.dummy");
	
    this->creditsImage = Game::instance().getResources().get(pathCredits);
    this->creditsClip.w = this->creditsImage->getWidth();

}
/**
* Unloads everything that was loaded.
* @see GameStateCredits::load
*/
void GameStateCredits::unload(){

	Log(DEBUG) << "\tUnloading credits...";
	this->creditsClip.y = 0;
	cleanEntities();

}
/**
* Renders the state.
* Always renders on 0,0 position.
* @see Sprite::render
*/
void GameStateCredits::render(){

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
