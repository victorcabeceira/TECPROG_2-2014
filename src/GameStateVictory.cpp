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

void GameStateVictory::load(){

	Log(DEBUG) << "Loading victory...";


    this->victoryImage = Game::instance().getResources().get("res/images/victory.png");
	this->lifeTime = 5.0;

	// Changing the music.
	Game::instance().getAudioHandler().changeMusic("res/audio/Tema_Victory_01.wav");

}

void GameStateVictory::unload(){

	Log(DEBUG) << "\tUnloading victory...";
	cleanEntities();

	this->passedTime = 0.0;
	this->lifeTime = 0.0;

}

void GameStateVictory::update(const double deltaTime_){

	this->passedTime += deltaTime_;

	if(this->passedTime >= this->lifeTime){

		Game::instance().setState(Game::GStates::CREDITS);
		return;

	}
}

void GameStateVictory::render(){

	if(this->victoryImage != nullptr){

		this->victoryImage->render(0, 0, nullptr, true);

	}
	else{

		Log(WARN) << "No image set for the victory screen!";

	}
}
