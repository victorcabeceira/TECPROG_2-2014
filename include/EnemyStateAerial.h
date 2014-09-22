#ifndef INCLUDE_ENEMYSTATEAERIAL_H
#define INCLUDE_ENEMYSTATEAERIAL_H

#include "StateEnemy.h"

class EnemyStateAerial : public StateEnemy {

	public:
	
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		EnemyStateAerial(Enemy* const enemy_);
		
		/**
		* The destructor.
		*/
		virtual ~EnemyStateAerial(){}

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

#endif // INCLUDE_ENEMYSTATEAERIAL_H
