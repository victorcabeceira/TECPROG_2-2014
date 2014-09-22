#ifndef INCLUDE_FADESCREEN_H
#define INCLUDE_FADESCREEN_H

#include "Entity.h"
#include "Sprite.h"
#include "FadeHandler.h"

class FadeScreen{

	public:
		
		/**
		* Fades the screen.
		*/
		FadeScreen();
		
		/**
		* Destructor method.
		*/
		virtual ~FadeScreen();
		
		/**
		* Updates the screen.
		*/
		void update(const double deltaTime_);
		
		/**
		* Renders the image.
		*/
		void render();
		
		/**
		* Check if the screen if faded.
		*/
		bool isFaded();
		
		/**
		* Fades out.
		*/
		void fadeOut(const double percentage_, const double time_);
		
		/**
		* Fades in.
		*/
		void fadeIn(const double percentage_, const double time_);

	private:
		Sprite* fadeImage;
		FadeHandler* fadeHandler;

};

#endif // INCLUDE_FADESCREEN_H
