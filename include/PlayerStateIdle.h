#ifndef INCLUDE_PlayerStateIdle_H
#define INCLUDE_PlayerStateIdle_H

#include "StatePlayer.h"

/**
* The state when the player is idle.
*
*/
class PlayerStateIdle : public StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		PlayerStateIdle(Player* const player_);
		
		/**
		* The destructor.
		*/
		virtual ~PlayerStateIdle(){}

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

#endif // INCLUDE_PlayerStateIdle_H
