#include "StatePlayer.h"

StatePlayer::StatePlayer(Player* const player_) :
	player(player_),
	box{0, 0, 0, 0}
{

}

StatePlayer::~StatePlayer(){
	this->player = nullptr;
}
