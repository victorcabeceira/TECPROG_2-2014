#ifndef INCLUDE_PSTATECLIMBING_H
#define INCLUDE_PSTATECLIMBING_H

#include "StatePlayer.h"

/**
* The state for when the player is not grounded.
* 
*/
class PlayerStateClimbing : public StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		PlayerStateClimbing(Player* const player_);

		/**
		* The destructor.
		*/
		virtual ~PlayerStateClimbing(){}

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

#endif // INCLUDE_PSTATECLIMBING_H
