#include "GameStateSplash.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>

/**
* The state for the initial splash screen.
* Game state that will contain the initial splash images, before the main menu state is called.
*/
GameStateSplash::GameStateSplash() :

	currentSplash(0),
	passedTime(0.0),
	lifeTime(0.0),
	ix(-300.0)

{

	for(unsigned int i = 0; i < SplashImages::TOTAL_SPLASH_IMAGES; i++){
		this->images[i] = nullptr;

	}
}

GameStateSplash::~GameStateSplash(){
}
/**
* Loads the level.
* From the Splash.lua script, loads all the necessary objects.
*/
void GameStateSplash::load(){

	Log(DEBUG) << "Loading splash screens...";

	LuaScript luaSplash("lua/Splash.lua");
	const std::string pathLogo = luaSplash.unlua_get<std::string>("splash.images.alke");
	const std::string pathTechs = luaSplash.unlua_get<std::string>("splash.images.techs");
	const std::string pathLicenses = luaSplash.unlua_get<std::string>("splash.images.licenses");
	const std::string pathEsrb = luaSplash.unlua_get<std::string>("splash.images.esrb");
	const double luaLifeTime = luaSplash.unlua_get<double>("splash.lifeTime");

	this->images[SplashImages::ALKE_LOGO] = Game::instance().getResources().get(pathLogo);
	this->images[SplashImages::TECHS] = Game::instance().getResources().get(pathTechs);
	this->images[SplashImages::LICENSES] = Game::instance().getResources().get(pathLicenses);
	this->images[SplashImages::ESRB] = Game::instance().getResources().get(pathEsrb);

	this->lifeTime = luaLifeTime;

}
/**
* Updates the objects within the StateGame.
* @param deltaTime_ : Delta time. Time elapsed between one frame and the other.
*/
void GameStateSplash::unload(){

	Log(DEBUG) << "\tUnloading splash screens...";
	this->currentSplash = 0;
	cleanEntities();

}
/**
* Unloads everything that was loaded.
* @see GameStateSplash::load
*/
void GameStateSplash::update(const double deltaTime_){

	this->passedTime += deltaTime_;

	Game::instance().getFade().fadeOut(0, 0.002);

	// Increment current image x position.
	if(this->ix < 0.0){

		this->ix += 5.0;

	}

	if(this->passedTime >= this->lifeTime){

		if(this->currentSplash >= SplashImages::TOTAL_SPLASH_IMAGES - 1){

			Game::instance().setState(Game::GameStates::MENU);

		}
		else{

			Game::instance().getFade().fadeIn(100, 0.002);
			this->passedTime = 0.0;
			this->ix = -300;
			this->currentSplash++;

		}
	}

	// Check if SPACE was pressed, to skip the splash images.
	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

	if(keyStates[GameKeys::SPACE] == true){

		Game::instance().setState(Game::GameStates::MENU);
		return;

	}

}
/**
* Renders the state.
* Always renders on 0,0 position.
* @see Sprite::render
*/
void GameStateSplash::render(){

	if(this->images[this->currentSplash] != nullptr){

		this->images[this->currentSplash]->render(this->ix, 0, nullptr, true);

	}
	else{

		Log(WARN) << "No image set for the splash screen!";

	}
}
