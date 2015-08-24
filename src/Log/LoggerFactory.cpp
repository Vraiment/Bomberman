//
//  LoggerFactory.cpp
//  Bomberman
//
//  Created on 06/12/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#include "LoggerFactory.hpp"

#include "Log.hpp"
#include "Logger.hpp"
#include "LogLevel.hpp"
#include "../Constants.hpp"
#include "../Utils/StringUtils.hpp"

#include <iostream>

using namespace std;
using namespace Bomberman::Constants;

namespace Bomberman {
	class StdOutLogger : public Logger {
	protected:
		void recieveLog(string text, LogLevel level) {
			cout << "[" << level.toString() << "]: " << text << endl;
		}
	};
	
	LoggerFactory LoggerFactory::singleton = LoggerFactory();
	
	LoggerFactory::LoggerFactory() {
		
	}
	
	LoggerFactory& LoggerFactory::get() {
		return singleton;
	}
	
	shared_ptr<Logger> LoggerFactory::getLogger(string loggerName) {
		shared_ptr<Logger> logger;
		
		loggerName = StringUtils::toUpper(loggerName);
		
		if (LOGGER_STD_OUT == loggerName) {
			if (!loggers.stdOut) {
				loggers.stdOut.reset(new StdOutLogger());
			}
			
			logger = loggers.stdOut;
		} else {
			Log::get() << "Invalid log name: \"" << loggerName << "\"." << LogLevel::warning;
		}
		
		return logger;
	}
}
