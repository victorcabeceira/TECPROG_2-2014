#include "StatePlayer.h"

// Constructor of StatePlayer, set the player.
StatePlayer::StatePlayer(Player* const player_) :
	player(player_),
	box{0, 0, 0, 0}
{

}

// Destructor method, runs when the class is deallocated.
StatePlayer::~StatePlayer(){
	this->player = nullptr;
}
