#include "Collision.h"
#include <cmath>

// Says if 2 rectangles are colliding.
bool Collision::rectsCollided(const SDL_Rect& firstRectangle, const SDL_Rect& secondRectangle){

    // Calculate the sides of rect A.
    const int leftFirstRectangle = firstRectangle.x;
    const int rightFirstRectangle = firstRectangle.x + firstRectangle.w;
    const int topFirstRectangle = firstRectangle.y;
    const int bottomFirstRectangle = firstRectangle.y + firstRectangle.h;

    // Calculate the sides of rect B.
    const int leftSecondRectangle = secondRectangle.x;
    const int rightSecondRectangle = secondRectangle.x + secondRectangle.w;
    const int topSecondRectangle = secondRectangle.y;
    const int bottomSecondRectangle = secondRectangle.y + secondRectangle.h;

    // If any of the sides from A are outside of B.
    if(bottomFirstRectangle <= topSecondRectangle || topFirstRectangle >= bottomSecondRectangle || 
        rightFirstRectangle <= leftSecondRectangle || leftFirstRectangle >= rightSecondRectangle){

        return false;

    }
    // If none of the sides from A are outside B.
    else{

        return true;

    }
}

// Return the side that first rectangle collides with the second rectangle. 
Collision::RectangleSide Collision::rectsCollidedSide(const SDL_Rect& firstRectangle, const SDL_Rect& secondRectangle){

    const double width = 0.5 * (firstRectangle.w + secondRectangle.w);
    const double height = 0.5 * (firstRectangle.h + secondRectangle.h);

    const double centerFirstRectangleOnX = firstRectangle.x + (firstRectangle.w / 2);
    const double centerFirstRectangleOnY = firstRectangle.y + (firstRectangle.h / 2);
    const double centerSecondRectangleOnX = secondRectangle.x + (secondRectangle.w / 2);
    const double centerSecondRectangleOnY = secondRectangle.y + (secondRectangle.h / 2);

    const double dx = centerFirstRectangleOnX - centerSecondRectangleOnX;
    const double dy = centerFirstRectangleOnY - centerSecondRectangleOnY;

    if (abs(dx) <= width && abs(dy) <= height){

        // collision is calculated here.
        const double relativeWidth = width * dy;
        const double relativeHeight = height * dx;

        if (relativeWidth > relativeHeight){

            if (relativeWidth > -relativeHeight){

                return RectangleSide::TOP;

            }
            else{
                
                return RectangleSide::LEFT;
            
            }
        }
        else{

            if (relativeWidth > -relativeHeight){
            
                return RectangleSide::RIGHT;
            
            }
            else{
            
                return RectangleSide::BOTTOM;
            
            }
        }
    }
    else{
        
        return RectangleSide::NONE;
    
    }
}
