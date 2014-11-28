#include "FadeScreen.h"
#include "Game.h"
#include "Logger.h"
#include "SafeDeallocation.h"


// Constructor, creates the fade handler.
FadeScreen::FadeScreen() :

	fadeImage(Game::instance().getResources().get("res/images/black_screen.png")),
	fadeHandler(new FadeHandler(this->fadeImage))

{
}

// Deallocate the resources used by fade screen.
FadeScreen::~FadeScreen() {

	SAFE_DELETE(this->fadeHandler);
	if(this->fadeHandler != nullptr){

		delete this->fadeHandler;
		this->fadeHandler = nullptr;

	}
}

// Update the fade screen.
void FadeScreen::update(const double deltaTime_){

	fadeHandler->update(deltaTime_);

}

// Render the fade screen.
void FadeScreen::render(){

	if(this->fadeImage != nullptr){

		this->fadeImage->render(0, 0, nullptr, true);

	}
}

// Check if the fade is concluded.
bool FadeScreen::isFaded(){

	bool faded = false;

	const int currentPercentage = this->fadeHandler->getCurrentPercentage();

	if(currentPercentage == 1.0){

		faded = true;

	}

	return faded;

}

// Fade the screen out.
void FadeScreen::fadeOut(const double percentage_, const double time_){

	this->fadeHandler->fadeOut(percentage_, time_);

}

// Fade the screen in.
void FadeScreen::fadeIn(const double percentage_, const double time_){

	this->fadeHandler->fadeIn(percentage_, time_);

}

