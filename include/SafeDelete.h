#pragma once

#define SAFE_DELETE(object); if(object != nullptr) {\
	delete object;\
	object = nullptr;\
}

#define SAFE_EXIT(state); if(state!=nullptr){\
	state->exit;\
}

#define SAFE_UNLOAD(state); if(state!=nullptr){\
	state->unload();\
}
