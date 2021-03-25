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
  int line, pos;
  
	Token(std::string t, std::string v, int l, int pos);
};

class Lexer {
public:
	int pos = 0;
	int index = 0;
	int line = 0;
	
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
	bool isAlphaNum(char ch);
	bool isIdentifier(char ch, bool includeNum);
	bool isSingleLineComment(char ch);
	bool isMultiLineComment(char ch);
	
	std::vector<Token> tokenize();
};