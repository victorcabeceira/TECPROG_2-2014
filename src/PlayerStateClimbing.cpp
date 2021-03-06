#include "PlayerStateClimbing.h"
#include "Logger.h"

bool isMoving = false;

void PlayerStateClimbing::enter(){
	
	std::string debug_enter ("STATE CLIMBING");

	Log(DEBUG) << debug_enter;

	this->player->isClimbing = true;
	
   	this->box.x = 58;
    this->box.y = 72;
    this->box.w = 130;
    this->box.h = 145;

    this->player->getAnimation()->changeAnimation(0, 6, 4, false, 1);

    this->player->vy = 0;

    
    
    if(!this->player->isRight){
		
		this->player->vx = -0.001;

    }
	else{
		
		this->player->vx = 0.0;
	
	}

}

void PlayerStateClimbing::exit(){
	
	this->player->isClimbing = false;
	isMoving = false;

}

void PlayerStateClimbing::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	int valueYAxis = this->player->vy;

    int currentFrame = this->player->getAnimation()->getCurrentFrame();

	this->player->moveVertical(keyStates_[GameKeys::UP], keyStates_[GameKeys::DOWN]);

	if(abs(valueYAxis)<1){
		
		this->player->getAnimation()->changeAnimation(currentFrame - 1,
			6, 1, false, 0);
			isMoving = true;
	
	}
	else{
		
		if(isMoving){
			
			this->player->getAnimation()->changeAnimation(0, 6, 4, false, 1);
			isMoving = false;
		
		}
	}

	// Jump
	if(keyStates_[GameKeys::SPACE]){
		
		std::string debug_handle("entrou");

		Log(DEBUG) << debug_handle;		
		this->player->vy = -700;

		if(this->player->isRight){
		
			this->player->vx = -500;
		
		}
		else{
		
			this->player->vx = 500;
		
		}

		this->player->changEnemyState(Player::PlayerStates::AERIAL);

		return;
	}

	if(!this->player->isClimbing){
		
		this->player->vy = -1000;

		this->player->changEnemyState(Player::PlayerStates::AERIAL);

		return;
	
	}

}

PlayerStateClimbing::PlayerStateClimbing(Player* const player_) :
	
	StatePlayer(player_)
{

}