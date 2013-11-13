//
//  Log.hpp
//  Bomberman
//
//  Created on 13/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Log__hpp__
#define __Log__hpp__

#include "LogLevel.hpp"

#include <string>
#include <sstream>

namespace Bomberman {
	class Logger;
	
	class Log {
	public:
		static Log& get();
		
		Log& operator<<(const char* value);
		Log& operator<<(std::string value);
		void operator<<(LogLevel level);
		
		void addLogger(std::shared_ptr<Logger> logger);
		
	private:
		Log(std::shared_ptr<Logger> logger);
		
		std::stringstream message;
		std::shared_ptr<Logger> logger;
		
		static Log singleton;
	};
}

#endif //__Log__hpp__
