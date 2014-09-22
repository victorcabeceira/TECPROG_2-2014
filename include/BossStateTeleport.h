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

};

#endif // INCLUDE_BOSSSTATETELEPORT_H
