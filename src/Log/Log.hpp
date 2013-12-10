//
//  Log.hpp
//  Bomberman
//
//  Created on 13/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Log__hpp__
#define __Log__hpp__

#include <exception>
#include <sstream>

namespace Bomberman {
	class Logger;
	class LogLevel;
	
	class Log {
	public:
		static Log& get();
		
		Log& operator<<(const char *value);
		Log& operator<<(std::string value);
		void operator<<(LogLevel level);
		void operator<<(std::exception exception);
		
		void addLogger(std::shared_ptr<Logger> logger);
		
	private:
		Log(std::shared_ptr<Logger> logger);
		
		void flush(LogLevel level);
		
		std::stringstream message;
		std::shared_ptr<Logger> logger;
		
		static Log singleton;
	};
}

#endif //__Log__hpp__
