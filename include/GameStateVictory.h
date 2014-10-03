#ifndef INCLUDE_GameStateVICTORY_H
#define INCLUDE_GameStateVICTORY_H

#include "StateGame.h"
#include "Sprite.h"

/**
* The state for the initial menu screen.
* Game state that will contain the game over screen.
*/
class GameStateVictory : public StateGame {

	public:
		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		GameStateVictory();

		/**
		* The destructor.
		*/
		virtual ~GameStateVictory();

		/**
		* Loads the level.
		* From the menu.lua script, loads all the necessary objects.
		*/
		virtual void load();

		/**
		* Updates the objects within the StateGame.
		* @param deltaTime_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(const double deltaTime_);

		/**
		* Unloads everything that was loaded.
		* @see GameStateVictory::load
		*/
		virtual void unload();

		/**
		* Renders the state.
		* Always renders on 0,0 position.
		* @see Sprite::render
		*/
		virtual void render();

	private:
		Sprite* victoryImage; /**< The image shown on the menu. */
		double passedTime; /**< The time already elapsed since the beggining of the menu. */
		double lifeTime; /**< The amount of time the menu will be shown. */

};

#endif // INCLUDE_GameStateVICTORY_H
