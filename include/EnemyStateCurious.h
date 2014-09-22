#ifndef INCLUDE_ESTATECURIOUS_H
#define INCLUDE_ESTATECURIOUS_H

#include "StateEnemy.h"

class EnemyStateCurious : public StateEnemy {

	public:
	
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		EnemyStateCurious(Enemy* const enemy_);
		
		/**
		* The destructor.
		*/
		virtual ~EnemyStateCurious(){}

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
		double timeElapsed;

};

#endif // INCLUDE_ESTATECURIOUS_H
