#ifndef INCLUDE_BOSSSTATEICEPRISION_H
#define INCLUDE_BOSSSTATEICEPRISION_H

#include "StateBoss.h"

class BossStateIcePrision : public StateBoss {

	public:
		
		/**
		* The constructor.
		* @param boss_ : Reference to the Boss.
		*/
		BossStateIcePrision(Boss* const boss_);
		
		/**
		* The destructor.
		*/
		virtual ~BossStateIcePrision(){}

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

#endif // INCLUDE_BOSSSTATEICEPRISION_H