#ifndef INCLUDE_BOSSSTATETELEPORT_H
#define INCLUDE_BOSSSTATETELEPORT_H

#include "StateBoss.h"

class BossStateTeleport : public StateBoss {

	public:
	
		/**
		* The constructor.
		* @param boss_ : Reference to the Boss.
		*/
		BossStateTeleport(Boss* const boss_);
		
		/**
		* The destructor.
		*/
		virtual ~BossStateTeleport(){}

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

		double teleportTime; /** Time that the Boss uses to do the attack*/
		double playerX; /** Player position in X axis*/
		double playerY; /** Player position in Y axis*/
		double powerCollisionWidth; /** Width of the power's collision*/
		double powerCollisionHeight; /** Height of the power's collision*/
		int axisOffset; /** Offsets the power's axis*/
		bool right; /** If the boss's attack is to the right*/
		int direction; /** The direction of the boss's attack*/

		const int START_TIME_TELEPORT = 3;
		const float MID_TIME_TELEPORT = 3.05;
		const int MID_END_TIME_TELEPORT = 4;
		const int MAX_TIME_TELEPORT = 5;



};

#endif // INCLUDE_BOSSSTATETELEPORT_H
