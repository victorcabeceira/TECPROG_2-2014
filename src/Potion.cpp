#include "Potion.h"
#include "Logger.h"
#include "Window.h"
#include <cmath>

Potion::Potion(const double x_, const double y_, const std::string& path_, const int strength_, const int inertia_,
	const int distance_, const bool isRight_) :

	DynamicEntity(x_, y_, path_),
	activated(true),
    canExplode(true),
    isExploding(true),
	strength(strength_),
	distance(distance_),
	flightTime(0.0),
    animation(nullptr)
{
    this->width = 192;

	this->isRight = isRight_;
	if(this->isRight){
		this->x -= this->width;
	}
    else{
        this->x -= this->width;   
    }
    
    this->animation = new Animation(0, 0, 192, 192, 13, false);

    this->y = this->y + 100;

    this->vx = 5 + abs(inertia_/80);    
    this->vy = 5;
}

Potion::~Potion(){

}

void Potion::update(const double dt_){

	const int angle = 360 - 45;
	const double gravity = 35;

    updateBoundingBox();
    this->animation->update(this->animationClip, dt_);

	const std::array<bool, CollisionSide::SOLID_TOTAL> detections = detectCollision();
    handleCollision(detections);

	if(this->activated){

        this->getAnimation()->changeAnimation(0, 0, 1, false, 0);

		this->flightTime +=dt_;

		const double speedXIdk = (this->distance/300.0)*(this->vx + this->strength * cos(angle/57.29) * flightTime);
		const double speedYIdk = (this->vy + this->strength * sin(angle/57.29) * flightTime - 0.5*gravity*flightTime*flightTime);

		if(this->isRight){
			this->x += speedXIdk;
		}
		else{
			this->x -= speedXIdk;
		}

		this->y -= speedYIdk;
	}
    else{
        if(this->canExplode){
            this->getAnimation()->changeAnimation(1, 0, 12, false, 0.8);
            this->canExplode = false;
        }
        if(this->getAnimation()->getCurrentFrame() == 12){
            this->isExploding =false;
        }
    }
}

void Potion::handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_){
    if(detections_.at(CollisionSide::SOLID_TOP)){ 
       if((int)this->y%64 > 0){
         	this->y += 64 -(int)this->y%64 + 1; 
         	this->strength = 0.0;
         	this->activated = false;
    	}
	}

    if(detections_.at(CollisionSide::SOLID_BOTTOM)){

    	this->strength = 0.0;
    	this->activated = false;
    }

    if(detections_.at(CollisionSide::SOLID_LEFT)){
        this->x -= (int)(this->x + this->width)%64 + 1;
        this->strength = 0.0;
        this->activated = false;
    }

    if(detections_.at(CollisionSide::SOLID_RIGHT)){
        if((int)this->x%64 > 0){
         	this->x += (64 - (int)this->x%64) + 1;
         	this->vx = 0.0;
        }
        this->activated = false;
    }
}

void Potion::render(const double cameraX_, const double cameraY_){
	
    const double dx = this->x - cameraX_ + this->width - 64;
    const double dy = this->y - cameraY_ - this->height;

    // // Actual.
    // SDL_Rect actualRect = {(int)dx, (int)dy, (int)this->width, (int)this->height};
    // SDL_SetRenderDrawColor( Window::getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    // SDL_RenderFillRect(Window::getRenderer(), &actualRect);

    // // Bounding box.
    // SDL_Rect boundingBox2 = {(int)(this->boundingBox.x - cameraX_), (int)(this->boundingBox.y - cameraY_), (int)this->boundingBox.w, (int)this->boundingBox.h};
    // SDL_SetRenderDrawColor( Window::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
    // SDL_RenderFillRect(Window::getRenderer(), &boundingBox2);

    if(this->sprite != nullptr && this->isExploding){
        this->sprite->render(dx, dy, &this->animationClip, false, this->vx*3/2, nullptr, SDL_FLIP_HORIZONTAL);
    }
}

void Potion::updateBoundingBox(){
	this->boundingBox.x = (int) this->x + this->width;
    this->boundingBox.y = (int) this->y - 32;
    this->boundingBox.w = (int) 32;
    this->boundingBox.h = (int) 32;
}

Animation* Potion::getAnimation(){
    return (this->animation);
}
