//
//  Logger.hpp
//  Bomberman
//
//  Created on 01/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Logger__hpp__
#define __Logger__hpp__

#include <string>

namespace Bomberman {
	enum LogLevel {
		info,
		warning,
		error,
		fatal
	};
	
	class Logger {
	public:
		virtual ~Logger();
		
		static void log(std::string text, LogLevel level);
		
		static void addLogger(std::shared_ptr<Logger> logger);
		
	protected:
		static std::string levelToString(LogLevel level);
		
		virtual void recieveLog(std::string text, LogLevel level) = 0;
		std::shared_ptr<Logger> next;
		
	private:
		static std::shared_ptr<Logger> singleton;
	};
}

#endif //__Logger__hpp__
