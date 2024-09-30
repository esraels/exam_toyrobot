#pragma once

#include <string>

namespace Tools {
	
	using namespace std;

	string& transformLower(string& s);
	string& transformUpper(string& s);
	string toLowerCase(string const& sVal);
	string toUpperCase(string const& sVal);
	string toLowerCase(const char* sc);
	string toUpperCase(const char* sc);

}