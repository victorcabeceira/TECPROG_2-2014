#ifndef INCLUDE_BOSSSTATEIDLE_H
#define INCLUDE_BOSSSTATEIDLE_H

#include "StateBoss.h"

class BossStateIdle : public StateBoss {

	public:
		
		/**
		* The constructor.
		* @param boss_ : Reference to the Boss.
		*/
		BossStateIdle(Boss* const boss_);
		
		/**
		* The destructor.
		*/
		virtual ~BossStateIdle(){}

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

#endif // INCLUDE_BOSSSTATEIDLE_H
