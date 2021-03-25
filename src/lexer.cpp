#include "../headers/lexer.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> keywords = { "set", "to"};
std::vector<char> integers = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
std::vector<char> punc = { ':', '{', '}' };
std::vector<char> operators = { '+', '-', '*', '/', '=' };

Token::Token(std::string t, std::string v){
	type = t;
	value = v;
};

Lexer::Lexer(std::string text) {
	input = text;
	character = text[0];
}

char Lexer::advance(int amount = 1) {
	pos += amount;
	index += amount;
	
	//check to make sure the index won't overflow the array length
	if (index > input.size() - 1) {
		return character = '\0';
	}

	character = input[index];

	return character;
}

char Lexer::peek(int amount = 1) {
	return input[pos + amount];
}

bool Lexer::isKeyword(std::string kw) {
  if (std::count(keywords.begin(), keywords.end(), kw)) return true;

	return false;
}

bool Lexer::isInteger(char ch) {
	if (std::count(integers.begin(), integers.end(), ch)) return true;
	
	return false;
}

bool Lexer::isPunc(char ch) {
	if (std::count(integers.begin(), integers.end(), ch)) return true;
	
	return false;
}

bool Lexer::isOperator(char ch) {
	if (std::count(operators.begin(), operators.end(), ch)) return true;
	
	return false;
}

bool Lexer::isLinebreak(char ch) {
	if (ch == '\n') return true;
	
	return false;
}

bool Lexer::isWhitespace(char ch) {
	if (ch == '\t' || ch == ' ') return true;
	
	return false;
}

std::vector<Token> Lexer::tokenize() {
	std::vector<Token> tokens = {};
	
	while (character != '\0') {
		if (isLinebreak(character)) {
			tokens.push_back(Token("Linebreak", "\n"));
		}
		
		if (isInteger(character)) {
			std::string num(1, character);
			std::string type = "Integer";
			
			advance();
			
			while (isInteger(character)) {
				num += character;
				advance();
			}
			
			if (character == '.' && isInteger(peek())) {
				type = "Float";
				num += character;
				
				advance();
				
				while(isInteger(character)) {
					num += character;
					advance();
				}
			}
			
			tokens.push_back(Token(type, num));
			
			advance();
		}
	}
	
	return tokens;
}