#include <iostream>

#include "headers/lexer.hpp"

int main() {
	Lexer lexer("5");
	
	std::vector<Token> tokens = lexer.tokenize();
	
	for (int i = 0; i < tokens.size(); i++) {
		std::cout << "<" << tokens[i].type << "> == " <<  tokens[i].value << std::endl;
	}
}