//
//  Logger.cpp
//  Bomberman
//
//  Created on 01/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Logger.hpp"

#include <iostream>

using namespace std;

namespace Bomberman {
	class StdOutLogger : public Logger {
	protected:
		void recieveLog(string text, LogLevel level) {
			cout << "[" << levelToString(level) << "]: " << text << endl;
		}
	};
	
	shared_ptr<Logger> Logger::singleton = shared_ptr<Logger>(new StdOutLogger());
	
	Logger::~Logger() {
		
	}
	
	string Logger::levelToString(LogLevel level) {
		switch (level) {
			case LogLevel::info: return "info";
			case LogLevel::warning: return "warning";
			case LogLevel::error: return "error";
			case LogLevel::fatal: return "fatal";
			default: throw FatalException();
		}
	}
	
	void Logger::log(string text, LogLevel level) {
		for (shared_ptr<Logger> current = singleton; current; current = current->next) {
			current->recieveLog(text, level);
		}
		
		if (level == LogLevel::fatal) {
			throw FatalException();
		}
	}
	
	void Logger::addLogger(std::shared_ptr<Logger> logger) {
		shared_ptr<Logger> current;
		
		for (current = singleton; current->next; current = current->next);
		
		current->next = logger;
	}
}
