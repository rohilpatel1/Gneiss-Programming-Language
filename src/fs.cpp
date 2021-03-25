#include "../headers/fs.hpp"
#include <iostream>
#include <string>
#include <fstream>

void Fs::writeFile(std::string file, std::string context) {
	std::ofstream f(file);

	f << context;

	f.close();
}

std::string Fs::readFile(std::string file) {
	std::string ctx, line;
	std::ifstream f(file);

	while (std::getline(f, line)) {
		ctx += (line + "\n");
	}

	return ctx;
}