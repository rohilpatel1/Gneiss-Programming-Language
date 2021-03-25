#pragma once
#include <iostream>
#include <string>
#include <vector>

/**
 * Note to self:
 * Index is for the array, it will only be increasing
 * Position is like index, but it resets to 0 when a newline happen
 **/

class Token {
public:
  std::string type, value;
	Token(std::string t, std::string v);
};

class Lexer {
public:
	int pos = 0;
	int index = 0;
	
	std::string input;
	char character;

	Lexer(std::string text);	
	
	char advance(int amount);
	char peek(int amount);
	
	bool isKeyword(std::string kw);
	bool isInteger(char ch);
	bool isPunc(char ch);
	bool isOperator(char ch);
	bool isLinebreak(char ch);
	bool isWhitespace(char ch);
	
	std::vector<Token> tokenize();
};