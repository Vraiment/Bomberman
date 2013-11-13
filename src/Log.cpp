//
//  Log.cpp
//  Bomberman
//
//  Created on 13/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Log.hpp"

#include "Logger.hpp"
#include "Exception.hpp"
#include <iostream>

using namespace std;

namespace Bomberman {
	class StdOutLogger : public Logger {
	protected:
		void recieveLog(string text, LogLevel& level) {
			cout << "[" << level.toString() << "]: " << text << endl;
		}
	};
	
	Log Log::singleton = Log(shared_ptr<Logger>(new StdOutLogger()));
	
	Log::Log(shared_ptr<Logger> logger) : logger(logger) {
		
	}
	
	Log& Log::get() {
		return singleton;
	}
	
	Log& Log::operator<<(const char* value) {
		message << value;
		
		return singleton;
	}
	
	Log& Log::operator<<(string value) {
		message << value;
		
		return singleton;
	}
	
	void Log::operator<<(LogLevel level) {
		for (auto current = logger; current; current = current->next) {
			current->recieveLog(message.str(), level);
		}
		
		message.str(string());
		message.clear();
		
		if (level == LogLevel::fatal) {
			throw FatalException();
		}
	}
	
	void Log::addLogger(shared_ptr<Logger> logger) {
		if (!logger) {
			get() << "Adding empty logger." << LogLevel::error;
			return;
		}
		
		shared_ptr<Logger> current = logger;
		
		while (current->next) {
			current = current->next;
		}
		
		current->next = logger;
	}
}