#include "GameSave.h"
#include "Logger.h"
#include <cstdlib>

std::string filePath = "";

GameSave::GameSave(){
}

/**
* Sets the save slot.
*/
void GameSave::setSlot(int saveSelection_){	
	
	switch(saveSelection_){
	
		case this->Selection::SLOT_1:
			this->filePath = "saveSlot1.dauphine";
		
		break;

		case this->Selection::SLOT_2:
			this->filePath = "saveSlot2.dauphine";
		
		break;

		case this->Selection::SLOT_3:
			this->filePath = "saveSlot3.dauphine";
		
		break;
	}
}

/**
* Creates the save.
*/
void GameSave::createSave(){
	
	this->saveFile.open(this->filePath.c_str());	

	if(!this->saveFile.fail()){
	
		this->saveFile << "-1" << std::endl;
		this->saveFile.close();
	
	}
	else
		Log(DEBUG) << "Could not create save file at " + this->filePath;

	return;

}

/**
* Saves the level.
*/
void GameSave::saveLevel(unsigned int level_, Player* player, std::vector <Enemy*> enemies, unsigned slot_){

	this->setSlot(slot_);	

	this->saveFile.open(this->filePath.c_str());

	Log(DEBUG) << "Saved from level " << level_;
	Log(DEBUG) << "Saved on file " << this->filePath;	

	if(!this->saveFile.fail()){
	
		this->currentLevel = level_;
		this->saveFile << this->currentLevel << std::endl;
		this->saveFile << player->x << std::endl;
		this->saveFile << player->y << std::endl;
		this->saveFile << enemies.size() << std::endl;
	
		for(auto enemy : enemies){
	
			this->saveFile << enemy->isDead() << " ";
	
		}
		
		this->saveFile.close();
	
	}
	else
		Log(DEBUG) << "Could not open save file at " + this->filePath;
}

/**
* Gets the saved level.
*/
int GameSave::getSavedLevel(int continueSelection_){
	
	this->saveSelection = continueSelection_;
	
	std::string level = "-1";

	if(this->saveSelection == 0){
	
		this->continueFile.open("saveSlot1.dauphine");
	
	}
	
	else if(this->saveSelection == 1){
	
		this->continueFile.open("saveSlot2.dauphine");
	
	}
	
	else if(this->saveSelection == 2){
	
		this->continueFile.open("saveSlot3.dauphine");
	
	}
	
	this->continueFile >> level;

	this->continueFile.close();

	return std::stoi(level);

}

/**
* Check if the game is saved.
*/
bool GameSave::isSaved(const int saveSlot_){

	this->setSlot(saveSlot_);	

	this->continueFile.open(this->filePath.c_str());

	std::string testSave = ""; 

	this->continueFile >> testSave;

	// Log(DEBUG) << "TestSave " << testSave;

	this->continueFile.close();

	if(testSave == "-1"){

		// Log(WARN) << "There is NO save at slot " << 1 + saveSlot_; 
		return false;

	}
	else{

		// Log(WARN) << "There is a save at slot " << 1 + saveSlot_;
		this->continueFile.close();
		return true;

	}
}

/**
* Gets the player position.
*/
void GameSave::getPlayerPosition(double& playerX_, double& playerY_, const int slot_){
	
	setSlot(slot_);

	this->continueFile.open(filePath.c_str(), std::ios_base::in);

	this->continueFile >> currentLevel; 

	this->continueFile >> playerX_;
	this->continueFile >> playerY_;

	this->continueFile.close();	

}

/**
* Checks if the enemy is dead.
*/
bool GameSave::isEnemyDead(const int numEnemy_, const int slot_){

	double skip = 0;

	int totalEnemies = 0;
	int currentEnemy = 0;

	bool rc = false;

	setSlot(slot_);

	this->continueFile.open(filePath.c_str(), std::ios_base::in);

	this->continueFile >> skip;
	this->continueFile >> skip;
	this->continueFile >> skip;

	this->continueFile >> totalEnemies;

	// Log(DEBUG) << "Total Enemies on Level " << totalEnemies;

	for(int i = 0; i < totalEnemies; i++){

		// Log(DEBUG) << "Is Enemy " << i << " dead?";		
		
		this->continueFile >> currentEnemy;

		// Log(DEBUG) << "Enemy under test dead status: " << currentEnemy;		

		if(i == numEnemy_){
		
			if(currentEnemy == 1)
		
				rc = true;

			break;			
		
		}
	}

	this->continueFile.close();	

	// if(rc)
	// 	Log(DEBUG) << "YES";		
	// else
	// 	Log(DEBUG) << "NO";		
			

	return rc;

}