#pragma once

/**
* Makes the safe deletion of the object
*/
#define SAFE_DELETE(object); if(object != nullptr) {\
	delete object;\
	object = nullptr;\
}

/**
* Exits the state safely
*/
#define SAFE_EXIT(state); if(state!=nullptr){\
	state->exit();\
}

/**
* Unloads the state safely
*/
#define SAFE_UNLOAD(state); if(state!=nullptr){\
	state->unload();\
}
