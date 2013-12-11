//
//  LexicalAnalyzer.cpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "LexicalAnalyzer.hpp"

#include <algorithm>

#include "../Utils/Exception.hpp"
#include "Token.hpp"

using namespace std;

namespace Bomberman {
	LexicalAnalyzer::LexicalAnalyzer() : token(&Token::eof) {
		
	}
	
	void LexicalAnalyzer::push(string str) {
		transform(str.begin(), str.end(), str.begin(), toupper);
		buffer += str;
	}
	
	Token LexicalAnalyzer::currentToken() const {
		return *token;
	}
	
	string LexicalAnalyzer::currentText() const {
		return text;
	}
	
	void LexicalAnalyzer::getNextToken() {
		throw NotImplementedException();
		
		enum state {
			start,
			id,
			number,
			end,
			error
		} currentState;
		
		string tmpText;
		bool done = false;
		
		//The valid patterns for tokens are:
		// (|)|.|;|DIGIT+|(_|LETTER)(_|LETTER|DIGIT)*
		
		while (!done) {
			switch (currentState) {
				case start:
					if (buffer.empty()) {
						token = &Token::eof;
						currentState = end;
					} else if (nextSymbol() == '(') {
						tmpText = nextSymbol();
						popSymbol();
						
						token = &Token::lPar;
						currentState = end;
					} else if (nextSymbol() == ')') {
						tmpText = nextSymbol();
						popSymbol();
						
						token = &Token::rPar;
						currentState = end;
					} else if (nextSymbol() == '.') {
						tmpText = nextSymbol();
						popSymbol();
						
						token = &Token::point;
						currentState = end;
					} else if (nextSymbol() == ';') {
						tmpText = nextSymbol();
						popSymbol();
						
						token = &Token::stop;
						currentState = end;
					} else if (isdigit(nextSymbol())) {
						tmpText = nextSymbol();
						popSymbol();
						
						currentState = number;
					} else if (isalpha(nextSymbol()) || nextSymbol() == '_') {
						tmpText = nextSymbol();
						popSymbol();
						
						currentState = id;
					} else {
						currentState = error;
					}
					break;
					
				case id:
					if (
						buffer.empty() ||
						nextSymbol() == '(' ||
						nextSymbol() == ')' ||
						nextSymbol() == '.' ||
						nextSymbol() == ';'
					) {
						currentState = end;
						token = &Token::identifier;
					} else if(
						isalnum(nextSymbol()) ||
						nextSymbol() == '_'
					) {
						tmpText += nextSymbol();
						popSymbol();
					} else {
						currentState = error;
					}
					break;
					
				case number:
					if (
						buffer.empty() ||
						nextSymbol() == '(' ||
						nextSymbol() == ')' ||
						nextSymbol() == '.' ||
						nextSymbol() == ';'
					) {
						currentState = end;
						token = &Token::number;
					} else if (isdigit(nextSymbol())) {
						tmpText += nextSymbol();
						popSymbol();
					} else {
						currentState = error;
					}
					
				case end:
					text = tmpText;
					done = true;
					break;
					
				default:
					token = &Token::error;
					currentState = end;
					break;
			}
		}
	}
	
	char LexicalAnalyzer::nextSymbol() {
		return buffer[0];
	}
	
	void LexicalAnalyzer::popSymbol() {
		buffer.erase(0, 1);
	}
}
