#ifndef INCLUDE_FADEHANDLER_H
#define INCLUDE_FADEHANDLER_H

#include "Sprite.h"

class FadeHandler {

	public:
	
		/**
		* Handles the fades.
		*/
		FadeHandler(Sprite* const sprite_);
		
		/**
		* Destructor method.
		*/
		virtual ~FadeHandler();

		/**
		* Fades in.
		*/
		void fadeIn(const double percentage_, const double time_);
		
		/**
		* Fades out.
		*/
		void fadeOut(const double percentage_, const double time_);
		
		/**
		* Updates the sprite.
		*/
		void update(const double dt_);
		
		/**
		* Gets the current percentage of fading.
		*/
		double getCurrentPercentage();

	private:
		bool shouldFadeIn;
		bool shouldFadeOut;
		double percentageOfStop;
		Sprite* sprite;
		double time;
		double currentPercentage;
		double rate;

};

#endif // INCLUDE_FADEHANDLER_H
