#ifndef INCLUDE_GAMESAVE_H
#define INCLUDE_GAMESAVE_H

#include <fstream>
#include "Player.h"
#include "Enemy.h"

class GameSave {

	public:
		GameSave();

		/**
		* Sets the save slot.
		*/
		void setSlot(int saveSelection);
		
		/**
		* Creates the save.
		*/
		void createSave();
		
		/**
		* Saves the level.
		*/
		void saveLevel(unsigned int level_, Player* player, std::vector <Enemy*> enemies, unsigned int slot_);
		
		/**
		* Gets the saved level.
		*/
		int getSavedLevel(int continueSelection_);
		
		/**
		* Gets the player position.
		*/
		void getPlayerPosition(double& playerX_, double& playerY_, const int slot_);
		
		/**
		* Checks if the enemy is dead.
		*/
		bool isEnemyDead(const int numEnemy_, const int slot_);
		
		/**
		* Check if the game is saved.
		*/
		bool isSaved(const int saveSlot_);

		std::string filePath;
		int saveSelection;
		unsigned int currentLevel;

		std::ofstream saveFile;
		std::ifstream continueFile;

		// Enumeration of save slots.
		enum Selection : uint8_t {
			SLOT_1 = 0,
			SLOT_2,
			SLOT_3,
			TOTAL
		};

};

#endif //INCLUDE_GAMESAVE_H