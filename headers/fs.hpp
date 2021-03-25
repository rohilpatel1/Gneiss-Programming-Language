#pragma once
#include <iostream>

class Fs {
public:
	void writeFile(std::string file, std::string context);
	std::string readFile(std::string file);
};