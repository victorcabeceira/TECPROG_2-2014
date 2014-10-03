#ifndef INCLUDE_PSTATECROUCHING_H
#define INCLUDE_PSTATECROUCHING_H

#include "StatePlayer.h"

/**
* The state when the player is idle.
*
*/
class PlayerStateCrouching : public StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		PlayerStateCrouching(Player* const player_);
		
		/**
		* The destructor.
		*/
		virtual ~PlayerStateCrouching(){}

		/**
		* @see StatePlayer::enter
		*/
		virtual void enter();

		/**
		* @see StatePlayer::exit
		*/
		virtual void exit();

		/**
		* @see StatePlayer::handleInput
		*/
		virtual void handleInput(const std::array<bool, GameKeys::MAX> keyStates_);

};

#endif // INCLUDE_PSTATECROUCHING_H
