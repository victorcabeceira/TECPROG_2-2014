#ifndef INCLUDE_BOSSSTATESHIELD_H
#define INCLUDE_BOSSSTATESHIELD_H

#include "StateBoss.h"

class BossStateShield : public StateBoss {

	public:
	
		/**
		* The constructor.
		* @param boss_ : Reference to the Boss.
		*/
		BossStateShield(Boss* const boss_);
		
		/**
		* The destructor.
		*/
		virtual ~BossStateShield(){}

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
		virtual void update(const double dt_);

};

#endif // INCLUDE_BOSSSTATESHIELD_H
