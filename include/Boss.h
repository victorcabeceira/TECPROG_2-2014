#ifndef INCLUDE_BOSS_H
#define INCLUDE_BOSS_H

#include "DynamicEntity.h"
#include "StateBoss.h"
#include "Animation.h"
#include "Potion.h"
#include <map>
#include <vector>
#include "Player.h"

class StateBoss;

class Boss : public DynamicEntity {

	public:

		enum BossStates : uint8_t {
			IDLE = 0,
			ATTACK,
			SHIELD,
			TELEPORT,
			ICEPRISION,
			MAGICPROJECTILE,
			DEAD
		};

		/**
		* The constructor.
		*/
		Boss(const double x_, const double y_, const std::string& path_, Player* const player_);

		/**
		* The destructor.
		*/
		virtual ~Boss();

		/**
		* Updates the player.
		* @see Player::updateInput, Player::updatePosition
		* @param deltaTime_ : Delta time. Time elapsed between one frame and the other, independent
		* 	of processing speed.
		*/
		virtual void update(const double deltaTime_);

		/**
		* Initializes the Boss's States
		*/
		void initializEnemyStates();

		/**
		* Destroys the Boss's States
		*/
		void destroyStates();

		/**
		* Changes the Boss's States
		*/
		void changEnemyState(const BossStates state_);

		/**
		* Renders the player.
		* Uses the player's sprite render method.
		* @see Sprite::render
		* @param cameraX_ : The x position of the camera.
		* @param cameraY_ : The y position of the camera.
		*/
		virtual void render(const double cameraX_, const double cameraY_);

		/**
		* Uses a Potion.
		*/
		void usePotion(const int strength_, const int distance_);
		
		/**
		* Gets the Boss's animation.
		*/
		Animation* getAnimation();

		/**
		* Checks if the Boss is Dead
		*/
		bool isDead();

		/**
		* Sets the Boss Dead
		*/
		void setDead(bool isDead_);

		/**
		* Enumerates Boss's skills
		*/
		enum BossSkills : uint8_t {
			BS_MAGIC_SHIELD = 0,
			BS_TELEPORT,
			BS_MAGIC_PROJECTILE,
			BS_INVOKE_WIND,
			BS_ICE_PRISION,
			BS_FINAL_SPLENDOR
		};

		/** 
		* Uses random skill.
		*/
		void randomSkill(const unsigned int index_);

		/**
		* Uses the teleport skill.
		*/
		bool teleport();

		/**
		* Uses the magic projectile skill.
		*/
		bool magicProjectile();

		/**
		* Uses the invoke wind skill.
		*/
		bool invokeWind();

		/**
		* Uses the ice prision skill.
		*/
		bool icePrision();

		/**
		* Uses the final splendor skill.
		*/
		bool finalSplendor();

		unsigned int potionsLeft; /**< Number of potions left */

		bool sawPlayer;	/**< Boolean to check if the Boss has seen the player*/
		std::vector<Potion*> potions; /**< Vector that contains the potions*/

		unsigned int life; /**< Quantity of the Boss's life*/
		bool hasShield; /**< Checks if the Boss has shield*/
		bool canWalk; /**< Checks if the Boss can walk*/
		Player* player; 
		Animation* powerAnimation;
		double powerX; /**< X position of the skill*/
		double powerY; /**< Y position of the skill*/
		bool powerIsActivated; /**< checks if the power is activated*/
		Sprite* power;
		SDL_Rect powerClip;
		SDL_RendererFlip powerFlip;
		Animation* shieldAnimation;
		Sprite* shield;
		SDL_Rect shieldClip;

	private:

		/**
		* Updates de Bounding Box of the Boss.
		*/
		virtual void updateBoundingBox();

		/**
		* Handle collision with the Boss.
		*/
		virtual void handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_);
		
		StateBoss* currentState;
		Animation* animation;
		std::map<BossStates, StateBoss*> statesMap;
		bool dead;

};

#endif // INCLUDE_BOSS_H
