#ifndef INCLUDE_PSTATEMOVINGCROUCH_H
#define INCLUDE_PSTATEMOVINGCROUCH_H

#include "StatePlayer.h"

/**
* The state when the player is idle.
*
*/
class PlayerStateMovingCrouch : public StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		PlayerStateMovingCrouch(Player* const player_);
		
		/**
		* The destructor.
		*/
		virtual ~PlayerStateMovingCrouch(){}

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

#endif // INCLUDE_PSTATEMOVINGCROUCH_H
