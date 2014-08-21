#include "CollisionRect.h"
#include "Logger.h"

CollisionRect::CollisionRect(const int x_, const int y_, const int w_, const int h_,
	const TypeCollision type_) :
	
	type(type_),
	rect{x_, y_, w_, h_}
{

}
		
CollisionRect::CollisionRect(const SDL_Rect rect_, const TypeCollision type_) :
	type(type_),
	rect(rect_)
{

}

CollisionRect::~CollisionRect(){

}

TypeCollision CollisionRect::stringToType(const std::string& strType_){
	if(strType_ == "collision"){
		return COLLISION;
	}
	else if(strType_ == "jump_through"){
		return JUMP_THROUGH;
	}
	else if(strType_ == "level_end"){
		return LEVEL_END;
	}
	else if(strType_ == "level_begin"){
		return LEVEL_BEGIN;
	}
	else if(strType_ == "level_end"){
		return LEVEL_END;
	}
	else if(strType_ == "climb"){
		return CLIMB;
	}
	else if(strType_ == "checkpoint"){
		return CHECKPOINT;
	}
	else if(strType_ == "cutscene"){
		return CUTSCENE;
	}
	else{
		Log(ERROR) << "Unknown collision type for " << strType_ << " .";
		return NONE;
	}
}
