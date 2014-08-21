#include "Util.h"
#include <sstream>

std::string Util::toString(const int number_){
	std::string result;
	std::ostringstream oss;
	oss.str("");
	oss.clear();
	oss << number_;
	result = oss.str();
	return result;
}
