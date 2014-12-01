#include "Level.h"
#include "Logger.h"
#include "Game.h"
#include "SafeDeallocation.h"

Level::Level() :
	
	width(0),
	height(0),
	player(nullptr),
	camera(nullptr),
	playerHud(nullptr),
	tileMap(nullptr),
	quadTree(nullptr),
	background(nullptr),
	backgroundTop(nullptr),
	checkpointsX{0,0,0,0,0},
	checkpointsY{0,0,0,0,0},
	checkpointsVisited{false,false,false,false,false},
	NUMBER_OF_CHECKPOINTS(5)

{
	
	// Only serves as the initializer for the derived classes.

}

Level::~Level(){
	this->player = nullptr;

	SAFE_DELETE(this->camera);
	SAFE_DELETE(this->playerHud);
	SAFE_DELETE(this->tileMap);
	SAFE_DELETE(this->quadTree);

}
/**
* @param camera_ : Sets the camera for the level.
* @note You should only set the camera after setting the player. Will warn if you
* 	didn't.
*/
void Level::changeCheckpoints(int NUMBER_OF_CHECKPOINTS_, std::vector <double> checkpointsX_,
		std::vector <double> checkpointsY_){
	
	this->checkpointsX = checkpointsX_;
	this->checkpointsY = checkpointsY_;
	this->NUMBER_OF_CHECKPOINTS = NUMBER_OF_CHECKPOINTS_;

}

unsigned int Level::getWidth(){
	
	return this->width;

}

unsigned int Level::getHeight(){
	
	return this->height;

}
/**
* @param player_ : Sets the player for the level.
*/
void Level::setPlayer(Player* const player_){
	
	this->player = player_;

	if(this->player != nullptr){
		
		this->player->setLevelWidthHeight(this->width, this->height);
		addEntity(this->player);
	
	}
	
	else{
	
		Log(WARN) << "Setting a null player for the level!";
	
	}
	
}

void Level::setCamera(Camera* const camera_){
	this->camera = camera_;

	if(this->camera != nullptr){
		
		if(this->player != nullptr){
			
			this->camera->setLevelWidthHeight(this->width, this->height);
		
		}
		else{
			
			Log(WARN) << "Shouldn't set the camera before the player, in Level!";
		
		}
	}
	else{
		Log(WARN) << "Setting a null camera!";
	}

}

void Level::setBoss(Boss* const boss_){
	this->boss = boss_;

	if(this->boss != nullptr){
		if(this->player != nullptr){
			this->boss->setLevelWidthHeight(this->width, this->height);
		}
		else{
			Log(WARN) << "Shouldn't set the boss before the player, in Level!";
		}
	}
	else{
		
		Log(WARN) << "Setting a null boss!";
	
	}

}

void Level::clearEnemies(){
	
	for(auto enemy : this->enemies){
		
		delete enemy;
		enemy = nullptr;
	
	}

	this->enemies.clear();
}

void Level::clearDocuments(){
	
	for(auto document : this->documents){
		
		delete document;
		document = nullptr;
	
	}

	this->documents.clear();

}
