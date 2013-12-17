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
	
	class OpeningFileErrorException : public Exception {
	public:
		virtual const char* what() const noexcept {
			return "error opening a file";
		}
	};
	
	class ParsingErrorException : public Exception {
	public:
		virtual const char* what() const noexcept {
			return "invalid value while parsing a string.";
		}
	};
}

#endif //__Exception__hpp__
