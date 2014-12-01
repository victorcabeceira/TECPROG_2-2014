#include "GameStateVictory.h"
#include "Game.h"
#include "Logger.h"

GameStateVictory::GameStateVictory() :

	victoryImage(nullptr),
	passedTime(0.0),
	lifeTime(0.0)

{
}

GameStateVictory::~GameStateVictory(){
}

/**
* Loads the level.
* From the menu.lua script, loads all the necessary objects.
*/
void GameStateVictory::load(){

	Log(DEBUG) << "Loading victory...";


    this->victoryImage = Game::instance().getResources().get("res/images/victory.png");
	this->lifeTime = 5.0;

	// Changing the music.
	Game::instance().getAudioHandler().changeMusic("res/audio/Tema_Victory_01.wav");

}
/**
* Unloads everything that was loaded.
* @see GameStateVictory::load
*/
void GameStateVictory::unload(){

	Log(DEBUG) << "\tUnloading victory...";
	cleanEntities();

	this->passedTime = 0.0;
	this->lifeTime = 0.0;

}
/**
* Updates the objects within the StateGame.
* @param deltaTime_ : Delta time. Time elapsed between one frame and the other.
*/
void GameStateVictory::update(const double deltaTime_){

	this->passedTime += deltaTime_;

	if(this->passedTime >= this->lifeTime){

		Game::instance().setState(Game::GameStates::CREDITS);
		return;

	}
}

/**
* Renders the state.
* Always renders on 0,0 position.
* @see Sprite::render
*/
void GameStateVictory::render(){

	if(this->victoryImage != nullptr){

		this->victoryImage->render(0, 0, nullptr, true);

	}
	else{

		Log(WARN) << "No image set for the victory screen!";

	}
}
