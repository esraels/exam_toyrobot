#include "Utils.h"

#include <algorithm>

namespace Tools {

	string& transformLower(string& s) {
		std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
		return s;  //also return it for one liner code.
	}
	
	string& transformUpper(string& s) {
		std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::toupper(c); });
		return s;  //also return it for one liner code.
	}

	string toLowerCase(string const& sVal) {
		string s = sVal;		//todo: (optimization) apply std::move if sVal is &&.
		return transformLower(s);
	}

	string toUpperCase(string const& sVal) {
		string s = sVal;        //todo: (optimization) apply std::move if sVal is &&.
		return transformUpper(s);
	}

	string toLowerCase(const char* sc) {
		return toLowerCase(string(sc));
	}
	string toUpperCase(const char* sc) {
		return toLowerCase(string(sc));
	}


}