#ifndef INCLUDE_GameStateMENU_H
#define INCLUDE_GameStateMENU_H

#include "StateGame.h"
#include "Sprite.h"
#include "Animation.h"

/**
* The state for the initial menu screen.
* Game state that will contain the main menu.
*/
class GameStateMenu : public StateGame {

	public:
	
		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		GameStateMenu();

		/**
		* The destructor.
		*/
		virtual ~GameStateMenu();

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
		* @see GameStateMenu::load
		*/
		virtual void unload();

		/**
		* Renders the state.
		* Always renders on 0,0 position.
		* @see Sprite::render
		*/
		virtual void render();
		
		/**
		* Handles the Selector Menu.
		*/
		void handleSelectorMenu();
		
		bool shouldIgnore;

	private:
		enum Selection : uint8_t {
			NEWGAME = 0,
			CONTINUE,
			OPTIONS,
			CREDITS,
			TOTAL
		};

		Sprite* menuImage; /**< The image shown on the menu. */
		Sprite* menuSelector; /**< The selector shown on the menu. */
		Sprite* attractModeBg; /**< The image shown on the menu. */
		Sprite* attractMode; /**< The selector shown on the menu. */
		double passedTime; /**< The time already elapsed since the beggining of the menu. */

		int currentSelection;
		int selectorXPositionLeft[Selection::TOTAL]; /**< The X position of the left selector.. */
		int selectorYPositionLeft[Selection::TOTAL]; /**< The Y position of the left selector.. */
		int selectorXPositionRight[Selection::TOTAL]; /**< The X position of the left selector.. */
		int selectorYPositionRight[Selection::TOTAL]; /**< The Y position of the left selector.. */

		const int attractHeightSize;
		const int attractChangeSpeed;
		SDL_Rect attractClip; /**< The clip shown on the credits. */

		Animation* shwingAnimation;
		bool shwingIsActivated;
		Sprite* shwing;
		SDL_Rect shwingClip;
};

#endif // INCLUDE_GameStateMENU_H