#ifndef INCLUDE_ENEMYSTATEALERT_H
#define INCLUDE_ENEMYSTATEALERT_H

#include "StateEnemy.h"

class EnemyStateAlert : public StateEnemy {

	public:
	
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		EnemyStateAlert(Enemy* const enemy_);
		
		/**
		* The destructor.
		*/
		virtual ~EnemyStateAlert(){}

		/**
		* @see StateEnemy::enter
		*/
		virtual void enter();

		/**
		* @see StateEnemy::exit
		*/
		virtual void exit();

		/**
		* @see StateEnemy::update
		*/
		virtual void update(const double dt_);

};

#endif // INCLUDE_ENEMYSTATEALERT_H
