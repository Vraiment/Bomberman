//
//  Token.cpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Token.hpp"

using namespace std;

namespace Bomberman {
	Token::Token(int value, string str) : value(value), str(str) {
		
	}
	
	std::string Token::toString() const {
		return str;
	}
	
	bool Token::operator==(const Token& other) const {
		return value == other.value;
	}
	
	bool Token::operator!=(const Token& other) const {
		return !(*this == other);
	}
	
	const Token Token::eof = Token(0, "eof");
	const Token Token::eol = Token(0, "eol");
	const Token Token::identifier = Token(0, "identifier");
}
