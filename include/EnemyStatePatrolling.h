#ifndef INCLUDE_EnemyStatePATROLLING_H
#define INCLUDE_EnemyStatePATROLLING_H

#include "StateEnemy.h"

class EnemyStatePatrolling : public StateEnemy {

	public:
	
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		EnemyStatePatrolling(Enemy* const enemy_);
		
		/**
		* The destructor.
		*/
		virtual ~EnemyStatePatrolling(){}

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

	private:
		double direction;
		const float RIGHT_DIRECTION = 1.0;
		const float LEFT_DIRECTION = -1.0;
};

#endif // INCLUDE_EnemyStatePATROLLING_H
