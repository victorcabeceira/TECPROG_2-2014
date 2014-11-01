#include "FadeScreen.h"
#include "Game.h"
#include "Logger.h"
#include "SafeDeallocation.h"


FadeScreen::FadeScreen() :

	fadeImage(Game::instance().getResources().get("res/images/black_screen.png")),
	fadeHandler(new FadeHandler(this->fadeImage))

{
}

FadeScreen::~FadeScreen() {

	SAFE_DELETE(this->fadeHandler);
	if(this->fadeHandler != nullptr){

		delete this->fadeHandler;
		this->fadeHandler = nullptr;

	}
}

void FadeScreen::update(const double deltaTime_){

	fadeHandler->update(deltaTime_);

}

void FadeScreen::render(){

	if(this->fadeImage != nullptr){

		this->fadeImage->render(0, 0, nullptr, true);

	}
}

bool FadeScreen::isFaded(){

	bool faded = false;

	const int currentPercentage = this->fadeHandler->getCurrentPercentage();

	if(currentPercentage == 1.0){

		faded = true;

	}

	return faded;

}

void FadeScreen::fadeOut(const double percentage_, const double time_){

	this->fadeHandler->fadeOut(percentage_, time_);

}

void FadeScreen::fadeIn(const double percentage_, const double time_){

	this->fadeHandler->fadeIn(percentage_, time_);

}

