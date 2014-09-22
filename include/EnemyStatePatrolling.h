#ifndef INCLUDE_ESTATEPATROLLING_H
#define INCLUDE_ESTATEPATROLLING_H

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

};

#endif // INCLUDE_ESTATEPATROLLING_H
