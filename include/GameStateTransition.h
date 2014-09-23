#ifndef INCLUDE_STATETRANSITION_H
#define INCLUDE_STATETRANSITION_H

#include "StateGame.h"
#include "Sprite.h"

/**
* The state for the initial splash screen.
* Game state that will contain the initial splash images, before the main menu state is called.
*/
class GameStateTransition : public StateGame {

	public:
		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		GameStateTransition();

		/**
		* The destructor.
		*/
		virtual ~GameStateTransition();

		/**
		* Loads the level.
		* From the Splash.lua script, loads all the necessary objects.
		*/
		virtual void load();

		/**
		* Updates the objects within the StateGame.
		* @param deltaTime_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(const double deltaTime_);

		/**
		* Unloads everything that was loaded.
		* @see GameStateTransition::load
		*/
		virtual void unload();

		/**
		* Renders the state.
		* Always renders on 0,0 position.
		* @see Sprite::render
		*/
		virtual void render();

	private:
		double passedTime; /**< The time already elapsed since the beggining of the splash. */
		double lifeTime; /**< The amount of time the splash will be shown. */
		Sprite* loading;
		Sprite* point;

};

#endif // INCLUDE_STATETRANSITION_H