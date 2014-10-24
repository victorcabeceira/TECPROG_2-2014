#include "Animation.h"

int animationCount = 0;

// Method that makes the animations of the game.
Animation::Animation(const int x_, const int y_, const int spriteWidth_,
					 const int spriteHeight_, const unsigned int numberOfImages_, const bool loop_) : 
	
	ANIMATION_LIMIT(10),   
	x(x_),
	y(y_),
	initialX(0),
	initialY(0),
	spriteWidth(spriteWidth_),
	spriteHeight(spriteHeight_),
	loop(loop_),
	totalElapsedTime(0.0),
	totalTime(0.0)

{
	if(numberOfImages_ == 0){
		this->numberOfImages = 1;
	}
	else {
		this->numberOfImages = numberOfImages_;
	}

}

// Destructor method, runs when the class is deallocated.
Animation::~Animation(){

}

void Animation::update(SDL_Rect& clip, const double deltaTime_){

	/* 
	* Compare the position on the sprite with the number of positions to know if is the
	* end of the animation.
	*/
	bool endOfAnimation = ((animationCount + 1) >= this->numberOfImages);

	const double deltaT = (this->totalTime / this->numberOfImages);

	// Check if the frame has changed.
    this->totalElapsedTime += deltaTime_;

    if(this->totalElapsedTime >= deltaT) {
        
        this->totalElapsedTime = 0;
        animationCount += 1;

        if(Animation::animationCount <= this->numberOfImages){

	        if(this->x < (int)ANIMATION_LIMIT){

	        	this->x += 1;

	        }
	        else{

	        	this->y += 1;
	        	this->x = 0;

	        }
    	}

    	if(endOfAnimation){

    		this->x= this->initialX;
    		this->y= this->initialY;
    		Animation::animationCount = 0;

    	}
    }

   	const int positionX_ = this->x * this->spriteWidth;
	const int positionY_ = this->y * this->spriteHeight;
	updateClip(clip, positionX_, positionY_);

}

// Method that changes the animation to another one.
void Animation::changeAnimation(const int x_, const int y_, const unsigned int numberOfImages_,
								const bool loop_, const double totalTime_){
	
	this->x = x_;
	this->y = y_;
	this->initialX = x_;
	this->initialY = y_;
	this->numberOfImages = (numberOfImages_ == 0) ? 1 : numberOfImages_;
	this->loop = loop_;
	this->totalTime = totalTime_;
	animationCount = 0;

}

void Animation::updateClip(SDL_Rect& clip, const int x_, const int y_){

	clip.x = x_;
	clip.y = y_;
	clip.w = this->spriteWidth;
	clip.h = this->spriteHeight;

}

// Return the current frame of the animation.
int Animation::getCurrentFrame(){
	
	return animationCount + 1;

}

// Return the current frame of the animation.
void Animation::changeWidthHeight(int width_, int height_){

	this->spriteWidth = width_;
	this->spriteHeight = height_;

}
