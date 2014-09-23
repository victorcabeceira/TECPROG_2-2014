#ifndef INCLUDE_DYNAMICENTITY_H
#define INCLUDE_DYNAMICENTITY_H

#include "Entity.h"
#include "Crosshair.h"
#include <array>

// Enumerates the collision sides.
enum CollisionSide : uint8_t {
	SOLID_TOP = 0,
	SOLID_BOTTOM,
	SOLID_RIGHT,
	SOLID_LEFT,
	SOLID_TOTAL
};

/**
* Subclass of Entity.
* The objects of this class are entities, but have physics applied to them (such as velocity).
*/
class DynamicEntity : public Entity {

	public:
	
		/**
		* The constructor.
		* Initializes all attributes.
		* @param x_ : position in x axis.
		* @param y_ : position in y axis.
		* @param sprite_ : which sprite to use.
		*/
		DynamicEntity(const double x_, const double y_, const std::string& path_);

		/**
		* The destructor.
		*/
		virtual ~DynamicEntity();

		/**
		* Make the entity jump.
		*/
		virtual void jump();
		
		/** 
		* Applies gravity to entity.
		*/
		virtual void applyGravity();
		
		/**
		* Moves the entity.
		*/
		virtual void move(const bool movingLeft_, const bool movingRight_);
		
		/**
		* Moves the entity vertically.
		*/
		virtual void moveVertical(const bool movingUp_, const bool movingDown_);
		
		/**
		* Slows the entity on x axis.
		*/
		virtual void slowVx();
		
		/**
		* Slows the entity on y axis.
		*/
		virtual void slowVy();
		
		/**
		* Make the entity roll.
		*/
		virtual void roll();
		
		/**
		* Aim the potions.
		*/
		virtual void aim(Crosshair* const crosshair, double direction);

		/**
		* Sets the level width and height
		* @param width_,height_ : Tells the player what the width and height of the level is.
		* @see Level::update()
		*/
		virtual void setlevelWidthHeight(const unsigned int width_, const unsigned int height_);

		double vx; /**< The dynamic entity's speed on the x axis. */
		double vy; /**< The dynamic entity's speed on the x axis. */
		double speed; /**< Speed that moves dynamic entity on input. */
		double maxSpeed; /**< Dynamic entity max speed. */		
		bool isGrounded; /**< Check for if the dynamic entity is on the ground. */
		double nextX;
		double nextY;
		bool reachedLevelEnd;

	    bool activated;
	    int strength;
	    int distance;
	    double flightTime;

	    bool isClimbing;

	protected:
	
		/**
		* Updates the position of the dynamic entity
		* Update is based on what input was recieved, and the players velocity.
		* @param deltaTime_ : Delta time. Time elapsed between one frame and the other, independent
		* 	of processing speed.
		*/
		virtual void updatePosition(const double deltaTime_);

		virtual void scoutPosition(const double deltaTime_); 

		/**
		* @return A bool array with the sides the DynamicEntity collided.
		*/
		virtual std::array<bool, CollisionSide::SOLID_TOTAL> detectCollision();

		/**
		* Handles the collision.
		*/
		virtual void handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_) = 0;

		virtual SDL_RendererFlip getFlip();

		virtual void updateBoundingBox() = 0;

		unsigned int levelWidth; /**< The width of the level. */
		unsigned int levelHeight; /**< The height of the level. */

};

#endif // INCLUDE_DYNAMICENTITY_H
