#include <iostream>
#include <fstream>

#include "headers/lexer.hpp"
#include "headers/fs.hpp"

void logTokens(std::string type, std::string value, int line, int pos) {
	std::string x = "{ type: " + type + ", value: \"" + value + "\", line: " + std::to_string(line) +  ", pos: " + std::to_string(pos) + " }";

	std::cout << x << std::endl;
}

int main() {
	Fs fs;

	std::string file = fs.readFile("tests/comments.gn");

	Lexer lexer(file);
	
	std::vector<Token> tokens = lexer.tokenize();
	
	for (int i = 0; i < tokens.size(); i++) {
		Token t = tokens[i];
		logTokens(t.type, t.value, t.line, t.pos);
	}
}