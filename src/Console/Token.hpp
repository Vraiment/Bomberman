//
//  Token.hpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Tokens__hpp__
#define __Tokens__hpp__

#include <string>

namespace Bomberman {
	class Token {
	friend class LexicalAnalyzer;
	public:
		static const Token eof;
		static const Token eol;
		static const Token stop;
		static const Token lPar;
		static const Token rPar;
		static const Token identifier;
		
		std::string toString() const;
		
		bool operator==(const Token& other) const;
		bool operator!=(const Token& other) const;
		
	private:
		Token(int value, std::string str);
		int value;
		std::string str;
	};
}

#endif //__Tokens__hpp__
