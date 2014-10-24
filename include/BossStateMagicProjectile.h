#ifndef INCLUDE_BOSSSTATEMAGICPROJECTILE_H
#define INCLUDE_BOSSSTATEMAGICPROJECTILE_H

#include "StateBoss.h"

class BossStateMagicProjectile : public StateBoss {

	public:
	
		/**
		* The constructor.
		* @param boss_ : Reference to the Boss.
		*/
		BossStateMagicProjectile(Boss* const boss_);
		
		/**
		* The destructor.
		*/
		virtual ~BossStateMagicProjectile(){}

		/**
		* @see StateBoss::enter.
		*/
		virtual void enter();

		/**
		* @see StateBoss::exit.
		*/
		virtual void exit();

		/**
		* @see StateBoss::update.
		*/
		virtual void update(const double deltaTime_);

		double projectileTime; /**Time that the projectile animation is on screen*/
		double magicProjectileX; /**Position in X of the magic projectile*/
		double magicProjectileY; /**Position in Y of the magic projectile*/
		double distanceBossPlayer; /**Distance between boss and player*/

		const int MAXIMUM_TIME = 3; /** Maximum time for magic projectile.*/
		const int CAST_START_X = 50; /** Distance between the start of the projectile in X and the boss in X*/
		const int CAST_START_Y = 150; /** Distance between the start of the projectile in Y and the boss in Y*/
		const int SPEED_FACTOR = 15; /** Multiplier factor for the speed of the projectile*/

};

#endif // INCLUDE_BOSSSTATEMAGICPROJECTILE_H
