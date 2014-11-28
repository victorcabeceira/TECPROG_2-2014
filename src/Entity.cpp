#include "Entity.h"
#include "Game.h"
#include "SDLWrapper.h"
#include "Logger.h"


//The Constructor of the Entity
Entity::Entity(const double x_, const double y_, const std::string& path_) :

    x(x_),
    y(y_),
    isRight(true),
    sprite(Game::instance().getResources().get(path_)),
    width(0),
    height(0),
    animationClip{0,0,0,0},
    boundingBox{(int)x_, (int)y_, 0, 0}

{
    // Only serves as the initializer for the derived classes.

    if(this->sprite != nullptr){

        this->width = this->sprite->getWidth();
        this->height = this->sprite->getHeight();
        
        this->boundingBox.w = this->width;
        this->boundingBox.h = this->height;

    }
    else{

        std::string warn_entity ("Entity sprite is null, width and height will be undefined.");

        Log(WARN) << warn_entity;

    }
}

//Initializer of the Entity and derived classes, as shown below.
Entity::Entity(const double x_, const double y_) :
   
    x(x_),
    y(y_),
    isRight(true),
    sprite(nullptr),
    width(0),
    height(0),
    animationClip{0,0,0,0},
    boundingBox{(int)x_, (int)y_, 0, 0}

{
    // Only serves as the initializer for the derived classes.
}

//Empty Constructor of the Entity class
Entity::~Entity(){
}

//Gets the width of the Entity
unsigned int Entity::getWidth(){

	return this->width;

}

//Gets the height of the Entity
unsigned int Entity::getHeight(){

	return this->height;

}

//Gest the clip to be shown by the library
SDL_Rect& Entity::getAnimationClip(){

	return this->animationClip;

}

//Gets the Box Collision Detection
SDL_Rect& Entity::getBoundingBox(){

    return this->boundingBox;

}

//Sets the collision
void Entity::setCollisionRects(const std::vector<CollisionRect>& collisionRects_){

    this->collisionRects = collisionRects_;   

}
