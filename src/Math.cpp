#include "Math.h"

// Return if a number is positive.
int Math::sign(const int number_){
	
    if(number_ > 0){ 
    	
        return 1;
    
    }
    else if(number_ < 0){
    	
        return -1;
    }
    else{
    	
        return 0;
    
    }
}

// Return if a number is positive.
int Math::sign(const double number_){
	
    if(number_ > 0.0){ 
    	
        return 1;
    }
    
    else if(number_ < 0.0){
    	
        return -1;
    
    }
    else{
    	
        return 0;
    
    }
}