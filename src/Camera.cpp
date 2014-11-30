#include "Camera.h"
#include "Configuration.h"
/**
* The camera class.
* Contains all the relevant implementation relative to the camera.
*/

/**
* The constructor.
* Initializes all the attributes.
* @param entity_ : The entity to centralize the camera on.
*/
Camera::Camera(Entity* const entity_):

    entity(entity_),
    levelWidth(0),
    levelHeight(0),
    clip{0, 0, (int)Configuration::getCameraDistanceWidth(), (int)Configuration::getCameraDistanceHeight()}

{
    /// @todo If the player changes the resolution, so should the clip. (?) (problem?)
}

/**
* The destructor.
*/
Camera::~Camera(){
}

/**
* Updates the camera.
* @see Camera::updatePosition
* Centralizes the player on the screen.
*/
void Camera::update(){

    updatePosition();

}

/**
* @return The camera clip (an SDL_Rect).
*/
SDL_Rect& Camera::getClip(){

    return this->clip;

}

/**
* Updates the cameras position.
* Based on the players position, change cameras position.
*/
void Camera::updatePosition(){

    this->clip.x = (this->entity->x + this->entity->getWidth() / 2) - (this->clip.w / 2);
    this->clip.y = (this->entity->y + this->entity->getHeight() / 2) - (this->clip.h / 2);

    // Left wall.
    if(this->clip.x < 0){

        this->clip.x = 0;

    }

    // Right wall.
    else if(this->clip.x > (int)this->levelWidth - this->clip.w){

        this->clip.x = (int)this->levelWidth - this->clip.w;

    }

    // Top wall.
    if(this->clip.y < 0){

        this->clip.y = 0;

    }

    // Bottom wall.
    else if(this->clip.y > (int)this->levelHeight - this->clip.h){

        this->clip.y = (int)this->levelHeight - this->clip.h;

    }
}

/**
* Changes the entity to centralize upon.
* @param entity_ : The entity to centralize the camera on.
*/
void Camera::centralizeOn(Entity* const entity_){

    this->entity = entity_;

}

/**
* @param width_,height_ : Tells the camera what the width and height of the level is.
* @see Level::update()
*/ 
void Camera::setLevelWidthHeight(const unsigned int width_, const unsigned int height_){

    this->levelWidth = width_;
    this->levelHeight = height_;

}
