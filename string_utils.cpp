#include<algorithm>
#include "string_utils.h"
std::string Utils::removeWhitespace(const char* argv) {
	std::string clean(argv);
	clean.erase(remove_if(clean.begin(), clean.end(), ::isspace), clean.end());
	return clean;
}