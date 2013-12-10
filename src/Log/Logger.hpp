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
	class LogLevel;
	
	class Logger {
	friend class Log;
	public:
		virtual ~Logger();
		
	protected:
		virtual void recieveLog(std::string text, LogLevel level) = 0;
		
	private:
		std::shared_ptr<Logger> next;
	};
}

#endif //__Logger__hpp__
