#include "FramesPerSecondWrapper.h"
#include "Logger.h"
#include "Configuration.h"

void FramesPerSecondWrapper::initialize(FPSmanager& fpsManager_){

	SDL_initFramerate(&fpsManager_);

	const int framerateIsSet = SDL_setFramerate(&fpsManager_, Configuration::getMaxFramerate());

	if(framerateIsSet == 0){

		Log(INFO) << "Successfully started the framerate manager.";

	}
	else{

		Log(WARN) << "Failed to start the framerate manager.";

	}
}

double FramesPerSecondWrapper::delay(FPSmanager& fpsManager_){

	return (double)(SDL_framerateDelay(&fpsManager_)/1000.0);

}
