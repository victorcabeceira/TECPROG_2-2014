#include "Util.h"
#include <sstream>

// Parse a int to a string.
std::string Util::toString(const int number_){
	
	std::string result;
	std::ostringstream oss;
	oss.str("");
	oss.clear();
	oss << number_;
	result = oss.str();
	return result;

}
