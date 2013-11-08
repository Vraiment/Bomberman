//
//  Pch.hpp
//  Bomberman
//
//  Created on 31/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Pch__hpp__
#define __Pch__hpp__

#include <exception>

namespace Bomberman {
	class Exception : public std::exception {
	public:
		virtual const char* what() const noexcept = 0;
	};
	
	class NotImplementedException : public Exception {
	public:
		virtual const char* what() const noexcept {
			return "action not implemented.";
		}
	};
	
	class FatalException : public Exception {
	public:
		virtual const char* what() const noexcept {
			return "fatal error";
		}
	};
}

#include "Logger.hpp"

const char dirSeparator = '/';

#endif //__Pch__hpp__
