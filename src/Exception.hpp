//
//  Exception.hpp
//  Bomberman
//
//  Created on 11/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Exception__hpp__
#define __Exception__hpp__

#include <exception>

namespace Bomberman {
	class Exception : public std::exception {
	public:
		virtual const char* what() const noexcept = 0;
	};
	
	class NotImplementedException : public Exception {
	public:
		virtual const char* what() const noexcept {
			return "action not implemented";
		}
	};
	
	class FatalException : public Exception {
	public:
		virtual const char* what() const noexcept {
			return "fatal error";
		}
	};
	
	class InvalidOperationException : public Exception {
	public:
		virtual const char* what() const noexcept {
			return "invalid operation";
		}
	};
}

#endif //__Exception__hpp__
