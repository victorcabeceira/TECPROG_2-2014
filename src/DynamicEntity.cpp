#include "DynamicEntity.h"
#include "Logger.h"
#include "Collision.h"
#include "Math.h"

DynamicEntity::DynamicEntity(const double x_, const double y_, const std::string& path_) :

	Entity(x_, y_, path_),
	vx(0.0),
	vy(0.0),
	speed(20.0),
	maxSpeed(550.0),
	isGrounded(false),
	nextX(x_),
	nextY(y_),
	reachedLevelEnd(false),
    activated(false),
    strength(0),
    distance(0),
    flightTime(0.0),
    isClimbing(false),
    levelW(0),
	levelH(0)

{
}

DynamicEntity::~DynamicEntity(){
}

void DynamicEntity::setLevelWH(const unsigned int width_, const unsigned int height_){

	this->levelW = width_;
	this->levelH = height_;

}

void DynamicEntity::updatePosition(const double dt_){

	((void)dt_); // Unused?

	this->x = this->nextX;
	this->y = this->nextY;
	this->isRight = (this->vx >= 0.0);

}

void DynamicEntity::scoutPosition(const double dt_){

	this->nextX += this->vx * dt_;
	this->nextY += this->vy * dt_;

}

std::array<bool, CollisionSide::SOLID_TOTAL> DynamicEntity::detectCollision(){

	std::array<bool, CollisionSide::SOLID_TOTAL> detections;
	detections.fill(false);

	for(auto tileBox : this->collisionRects){

		const Collision::RectangleSide side = Collision::rectsCollidedSide(this->boundingBox, tileBox.rect);

		if(side != Collision::RectangleSide::NONE){

			if(tileBox.type == LEVEL_END){

				this->reachedLevelEnd = true;

			}

			switch(side) {

				case Collision::RectangleSide::TOP: // Hitting under the tile.
					detections.at(SOLID_TOP) = (tileBox.type != JUMP_THROUGH) ? true : false;

					break;

				case Collision::RectangleSide::BOTTOM: // Hitting top of the tile.
					detections.at(SOLID_BOTTOM) = true;

					if(tileBox.type == JUMP_THROUGH){

						// Going up, not colliding
						if(this->vy < 0) {						

							detections.at(SOLID_BOTTOM) = false;
							//Log(DEBUG) << "Up and go";

						}else

						// Going down and goes through tile top
						if(this->vy >= 0.0 && (this->boundingBox.y + this->boundingBox.h) > tileBox.rect.y + tileBox.rect.h){

							detections.at(SOLID_BOTTOM) = false;
							//Log(DEBUG) << "Not so fast";

						}
						else{

							detections.at(SOLID_BOTTOM) = true;
							//Log(DEBUG) << "Stop on top";

						}
					}

					break;

				case Collision::RectangleSide::RIGHT: // Hitting right side of the tile.
					detections.at(SOLID_RIGHT) = (tileBox.type != JUMP_THROUGH) ? true : false;

					if(tileBox.type == CLIMB && !this->isGrounded){

						// Log(DEBUG) << "CLIMB RIGHT";
						this->isClimbing = true;

					}
					else{

						if(this->isClimbing){

							// Log(DEBUG) << "EXIT CLIMB right";
							this->isClimbing = false;

						}
					}

					break;

				case Collision::RectangleSide::LEFT: // Hitting left side of the tile.
					detections.at(SOLID_LEFT) = (tileBox.type != JUMP_THROUGH) ? true : false;

					if(tileBox.type == CLIMB && !this->isGrounded){

						// Log(DEBUG) << "~~~~ CLIMB LEFT";
						this->isClimbing = true;

					}
					else{

						if(this->isClimbing){

							// Log(DEBUG) << "EXIT CLIMB left";
							this->isClimbing = false;

						}
					}

					break;

				default:

					Log(ERROR) << "Unknown rectangle side collided with a dynamic entity.";

					break;

			}
		}
		else{
			// No collision.
		}		
	}

	return detections;

}

void DynamicEntity::jump(){

	this->vy = (-1) * 1210.0;

}

void DynamicEntity::applyGravity(){

	if(this->vy + 50 < this->maxSpeed*2){

		this->vy += 50;

	}
}

void DynamicEntity::move(const bool movingLeft_, const bool movingRight_){

	const double turnHandle = 5.5;

	if(movingLeft_ || movingRight_){

		if(movingLeft_){

			if(this->vx > 0.0){

				this->vx -= this->speed * turnHandle;

			}
			else{

				this->vx -= this->speed;

			}
			
			this->vx = (this->vx < -this->maxSpeed) ? -this->maxSpeed : this->vx;

		}

		if(movingRight_){

			if(this->vx < 0.0){

				this->vx += this->speed * turnHandle;

			}
			else{

				this->vx += this->speed;

			}

			this->vx = (this->vx > this->maxSpeed) ? this->maxSpeed : this->vx;

		}
	}
	else{

		slowVx();

	}

}

void DynamicEntity::moveVertical(const bool movingUp_, const bool movingDown_){

	const double turnHandle = 5.5;

	if(movingUp_ || movingDown_){

		if(movingUp_){

			if(this->vy > 0.0){

				this->vy -= this->speed * turnHandle;

			}
			else{

				this->vy -= this->speed;

			}
			
			this->vy = (this->vy < -this->maxSpeed) ? -this->maxSpeed : this->vy;

		}

		if(movingDown_){

			if(this->vy < 0.0){

				this->vy += this->speed * turnHandle;

			}
			else{

				this->vy += this->speed;

			}

			this->vy = (this->vy > this->maxSpeed) ? this->maxSpeed : this->vy;

		}
	}
	else{

		slowVy();

	}

}

void DynamicEntity::slowVx(){

	const int vsign = Math::sign(this->vx);
	this->vx -= 100 * vsign;

	if (Math::sign(this->vx) != vsign) {

        this->vx = 0.0001 * vsign;

	}
}

void DynamicEntity::slowVy(){

	const int vsign = Math::sign(this->vy);
	this->vy -= 1000 * vsign;

	if (Math::sign(this->vy) != vsign) {

        this->vy = 0.0001 * vsign;

	}
}

void DynamicEntity::roll(){

	const double rollStrength = 120.0;

	if(this->isRight){

		this->vx = rollStrength * this->speed;

	}
	else{

		this->vx = -rollStrength * this->speed;

	}
}

void DynamicEntity::aim(Crosshair* const crosshair, const double direction){

	const double velocity = 10.0;
	crosshair->x += velocity * direction;

}

SDL_RendererFlip DynamicEntity::getFlip(){

	SDL_RendererFlip flip = SDL_FLIP_NONE;

	if(!this->isRight){

		flip = SDL_FLIP_HORIZONTAL;

	}

	return flip;

}
