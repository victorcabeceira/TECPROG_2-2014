#include "StateGame.h"

	/**
	* The destructor.
	*/

StateGame::~StateGame(){

	// Should be called in each state unload.
	cleanEntities();

}

	/**
	* Adds an entity to the vector.
	*/

void StateGame::addEntity(Entity* const entity){

	this->entities.push_back(entity);

}

	/**
	* Deletes all the entities inside the vector.
	*/

void StateGame::cleanEntities(){

	for(auto entity : this->entities){
		
		delete entity;
		entity = nullptr;
	
	}

	this->entities.clear();
}
