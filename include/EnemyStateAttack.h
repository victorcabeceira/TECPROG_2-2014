#ifndef INCLUDE_EnemyStateATTACK_H
#define INCLUDE_EnemyStateATTACK_H

#include "StateEnemy.h"

class EnemyStateAttack : public StateEnemy {

	public:
	
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		EnemyStateAttack(Enemy* const enemy_);
		
		/**
		* The destructor.
		*/
		virtual ~EnemyStateAttack(){}

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

#endif // INCLUDE_EnemyStateATTACK_H
