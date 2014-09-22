#ifndef INCLUDE_PlayerStateRolling_H
#define INCLUDE_PlayerStateRolling_H

#include "StatePlayer.h"

/**
* The state when the player is rolling.
*
*/
class PlayerStateRolling : public StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		PlayerStateRolling(Player* const player_);
		
		/**
		* The destructor.
		*/
		virtual ~PlayerStateRolling(){}

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

#endif // INCLUDE_PlayerStateRolling_H
