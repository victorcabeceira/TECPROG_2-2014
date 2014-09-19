#ifndef INCLUDE_ESTATEIDLE_H
#define INCLUDE_ESTATEIDLE_H

#include "StateEnemy.h"

class EnemyStateIdle : public StateEnemy {

	public:
	
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		EnemyStateIdle(Enemy* const enemy_);
		
		/**
		* The destructor.
		*/
		virtual ~EnemyStateIdle(){}

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

#endif // INCLUDE_ESTATEIDLE_H
