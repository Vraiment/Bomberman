//
//  TokenFactory.hpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __TokenFactory__hpp__
#define __TokenFactory__hpp__

#include <string>

#include "Token.hpp"

namespace Bomberman {
    class TokenFactory {
    public:
        TokenFactory();
        
        void push(std::string string);
        
        std::string lexeme() const;
        
        Token currentToken() const;
        Token nextToken() const;
        
        bool empty() const;
        void clear();
        
        void popToken();
        TokenFactory& operator<<(std::string string);
        
    private:
        void processToken();
        
        char nextSymbol();
        void popSymbol();
        
        bool processing;
        Token cToken, nToken;
        std::string cLexeme, nLexeme;
        std::string buffer;
    };
}

#endif //__TokenFactory__hpp__
