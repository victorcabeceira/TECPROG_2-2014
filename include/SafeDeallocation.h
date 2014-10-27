#pragma once

#define SAFE_DELETE(object); if(object != nullptr) {\
	delete object;\
	object = nullptr;\
}
