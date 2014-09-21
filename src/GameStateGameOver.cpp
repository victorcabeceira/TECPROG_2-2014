#include "GameStateGameOver.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>

GameStateGameOver::GameStateGameOver() :

	gameOverImage(nullptr),
	passedTime(0.0),
	lifeTime(0.0)

{
}

GameStateGameOver::~GameStateGameOver(){
}

void GameStateGameOver::load(){

	Log(DEBUG) << "Loading Game Over...";

	LuaScript luaGameOver("lua/GameOver.lua");
	const std::string pathGameOver = luaGameOver.unlua_get<std::string>("gameOver.images.gameOver");
	const double luaLifeTime = luaGameOver.unlua_get<double>("gameOver.lifeTime");

    this->gameOverImage = Game::instance().getResources().get(pathGameOver);
	this->lifeTime = luaLifeTime;

	// Changing the music.
	Game::instance().getAudioHandler().changeMusic("res/audio/Game_Over.mid");

}

void GameStateGameOver::unload(){

	Log(DEBUG) << "\tUnloading Game Over...";
	cleanEntities();

	this->passedTime = 0.0;
	this->lifeTime = 0.0;

	Game::instance().getAudioHandler().stopMusic();

}

void GameStateGameOver::update(const double dt_){

	this->passedTime += dt_;

	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

	if(keyStates[GameKeys::SPACE] || keyStates[GameKeys::LATTACK]){

		Game::instance().setState(Game::GStates::MENU);
		return;

	}

	if(this->passedTime >= this->lifeTime){

		Game::instance().setState(Game::GStates::MENU);
		return;

	}
}

void GameStateGameOver::render(){

	if(this->gameOverImage != nullptr){

		this->gameOverImage->render(0, 0, nullptr, true);

	}
	else{

		Log(WARN) << "No image set for the game over screen!";

	}
}
