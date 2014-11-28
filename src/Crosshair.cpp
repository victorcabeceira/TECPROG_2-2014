#include "Crosshair.h"

//Constructor of the Crosshair
Crosshair::Crosshair(const double x_, const double y_, const std::string& path_) :

	Entity(x_, y_, path_),
	activated(false)

{
}

Crosshair::~Crosshair(){
}


//Updates the crosshair itself
void Crosshair::update(const double deltaTime_){

	((void)deltaTime_); // Unused.

}

//Render the crosshair of potions		
void Crosshair::render(const double cameraX_, const double cameraY_){

	if(this->activated && this->sprite != nullptr){

        const double dx = this->x - cameraX_;
        const double dy = this->y - cameraY_;
        this->sprite->render(dx, dy, nullptr, false, 0.0, nullptr, SDL_FLIP_HORIZONTAL);

    }
}

//Gets the Width of the Crosshair
unsigned int Crosshair::getWidth(){

	return this->width;

}

//Gets the Height of the Crosshair
unsigned int Crosshair::getHeight(){

	return this->height;

}
