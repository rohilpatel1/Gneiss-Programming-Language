#include "../headers/lexer.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> keywords = { "set", "to"};
std::vector<char> integers = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
std::vector<char> punc = { ':', '{', '}', ',', '(', ')' };
std::vector<char> operators = { '+', '-', '*', '/', '=' };

Token::Token(std::string t, std::string v, int l, int p){
	type = t;
	value = v;
	line = l;
	pos = p;
};

Lexer::Lexer(std::string text) {
	line = 1;
	pos = 0;

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
	if (std::count(punc.begin(), punc.end(), ch)) return true;
	
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

bool Lexer::isAlphaNum(char ch) {
	return (ch >= 'a' && 'z' >= ch) || (ch >= 'A' && 'Z' >= ch);
}

bool Lexer::isIdentifier(char ch, bool includeNum) {
	if (!includeNum)
    return isAlphaNum(ch) || isInteger(ch);
	else
		return isAlphaNum(ch);
}

bool Lexer::isSingleLineComment(char ch) {
	if (ch == '&') return true;

	return false;
}

bool Lexer::isMultiLineComment(char ch) {
	if (ch == '~') return true;

	return false;
}

std::vector<Token> Lexer::tokenize() {
	std::vector<Token> tokens = {};

	int lastIndex = index;
	
	while (character != '\0') {
		if (isWhitespace(character)) advance();

		if (isLinebreak(character)) {
			tokens.push_back(Token("Linebreak", "\n", line, pos));

			advance();

			line++;
			pos = 0;
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
			
			tokens.push_back(Token(type, num, line, pos));
			
			advance();
		}
		
		if (isPunc(character)) {
			std::string punc(1, character);

			advance();
			
			if (isPunc(character)) punc += character;
			
			tokens.push_back(Token("Punctuation", punc, line, pos));

			advance();
		}

		if (isOperator(character)) {
			std::string op(1, character);

			advance();

			if (isOperator(character)) op += character;

			tokens.push_back(Token("Operator", op, line, pos));

			advance();
		}

		if (isIdentifier(character, true)) {
			std::string str(1, character);
			std::string type = "";

			advance();

			while(character != '\0' && isIdentifier(character, false)) {
				str += character;
				advance();
			}

			if (std::count(keywords.begin(), keywords.end(), str)) 
				type = "Keyword";
			else
				type = "Identifier";

			tokens.push_back(Token(type, str, line, pos));
		}

		if (isSingleLineComment(character)) {
			advance();
			while (!isLinebreak(character)) advance();

			advance();
			line++;
			pos = 0;

		}

		if (isMultiLineComment(character)) {
			advance();
			while (!isMultiLineComment(character)) {
				if (isLinebreak(character)) {
					advance();
					line++;
					pos = 0;
				} else {
					advance();
				}
			}
			advance();
		}

		if (lastIndex == index) {
			std::cout << character << " is not a valid character!" << std::endl;
		}
	}

	tokens.push_back(Token("EOF", "EOF", line + 1, 0));
	
	return tokens;
}