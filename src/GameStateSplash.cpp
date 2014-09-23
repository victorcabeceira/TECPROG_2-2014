#include "GamEnemyStateSplash.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>

GamEnemyStateSplash::GamEnemyStateSplash() :

	currentSplash(0),
	passedTime(0.0),
	lifeTime(0.0),
	ix(-300.0)

{

	for(unsigned int i = 0; i < SplashImages::TOTAL_SPLASH_IMAGES; i++){
		this->images[i] = nullptr;

	}
}

GamEnemyStateSplash::~GamEnemyStateSplash(){
}

void GamEnemyStateSplash::load(){

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

void GamEnemyStateSplash::unload(){

	Log(DEBUG) << "\tUnloading splash screens...";
	this->currentSplash = 0;
	cleanEntities();

}

void GamEnemyStateSplash::update(const double deltaTime_){

	this->passedTime += deltaTime_;

	Game::instance().getFade().fadeOut(0, 0.002);

	// Increment current image x position.
	if(this->ix < 0.0){

		this->ix += 5.0;

	}

	if(this->passedTime >= this->lifeTime){

		if(this->currentSplash >= SplashImages::TOTAL_SPLASH_IMAGES - 1){

			Game::instance().setState(Game::GStates::MENU);

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

		Game::instance().setState(Game::GStates::MENU);
		return;

	}

}

void GamEnemyStateSplash::render(){

	if(this->images[this->currentSplash] != nullptr){

		this->images[this->currentSplash]->render(this->ix, 0, nullptr, true);

	}
	else{

		Log(WARN) << "No image set for the splash screen!";

	}
}
