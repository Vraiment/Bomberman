//
//  LexicalAnalyzer.hpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __LexicalAnalyzer__hpp__
#define __LexicalAnalyzer__hpp__

#include <string>

namespace Bomberman {
	class Token;
	
	class LexicalAnalyzer {
	public:
		LexicalAnalyzer();
		
		void push(std::string string);
		
		Token currentToken() const;
		std::string currentText() const;
		
		void getNextToken();
		
	private:
		char nextSymbol();
		void popSymbol();
		
		const Token *token;
		std::string text;
		std::string buffer;
	};
}

#endif //__LexicalAnalyzer__hpp__
