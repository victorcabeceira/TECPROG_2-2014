#include "StatePlayer.h"

	/**
	* The constructor.
	* @param player_ : Reference to the player.
	*/
StatePlayer::StatePlayer(Player* const player_) :
	
	player(player_),
	box{0, 0, 0, 0}

{

}

	/**
	* The destructor.
	*/
StatePlayer::~StatePlayer(){
	
	this->player = nullptr;

}
