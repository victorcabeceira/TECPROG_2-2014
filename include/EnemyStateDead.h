#ifndef INCLUDE_EnemyStateDEAD_H
#define INCLUDE_EnemyStateDEAD_H

#include "StateEnemy.h"

class EnemyStateDead : public StateEnemy {

	public:
	
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		EnemyStateDead(Enemy* const enemy_);
		
		/**
		* The destructor.
		*/
		virtual ~EnemyStateDead(){}

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
		virtual void update(const double deltaTime_);

};

#endif // INCLUDE_EnemyStateDEAD_H
