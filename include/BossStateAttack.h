#ifndef INCLUDE_BOSSSTATEATTACK_H
#define INCLUDE_BOSSSTATEATTACK_H

#include "StateBoss.h"

class BossStateAttack : public StateBoss {

	public:

		/**
		* The constructor.
		* @param boss_ : Reference to the Boss.
		*/
		BossStateAttack(Boss* const boss_);
		
		/**
		* The destructor.
		*/
		virtual ~BossStateAttack(){}

		/**
		* @see StateBoss::enter
		*/
		virtual void enter();

		/**
		* @see StateBoss::exit
		*/
		virtual void exit();

		/**
		* @see StateBoss::update
		*/
		virtual void update(const double deltaTime_);

		int attackIndex; /** The index of the attack that the boss will use.*/

		const int RANDOM_ATTACK = 4; /**Number of possibilities for the attack index*/

};

#endif // INCLUDE_BOSSSTATEATTACK_H
