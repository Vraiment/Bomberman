//
//  LexicalAnalyzer.cpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "LexicalAnalyzer.hpp"

#include "../Utils/Exception.hpp"
#include "Token.hpp"

using namespace std;

namespace Bomberman {
	LexicalAnalyzer::LexicalAnalyzer() : token(nullptr) {
		
	}
	
	void LexicalAnalyzer::push(string str) {
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
	}
	
	char LexicalAnalyzer::nextSymbol() {
		return buffer[0];
	}
	
	void LexicalAnalyzer::popSymbol() {
		buffer.erase(0, 1);
	}
}
