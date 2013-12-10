//
//  LogLevel.cpp
//  Bomberman
//
//  Created on 13/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "LogLevel.hpp"

#include "../Utils/Exception.hpp"

namespace Bomberman {
	LogLevel::LogLevel(int type) : type(type) {
		
	}
	
	const char* LogLevel::toString() const {
		switch (type) {
			case 0: return "info";
			case 1: return "warning";
			case 2: return "error";
			case 3: return "fatal";
			default: throw InvalidOperationException();
		}
	}
	
	bool LogLevel::operator==(const LogLevel& other) const {
		return type == other.type;
	}
	
	bool LogLevel::operator!=(const LogLevel& other) const {
		return !(*this == other);
	}
	
	const LogLevel LogLevel::info = LogLevel(0);
	const LogLevel LogLevel::warning = LogLevel(1);
	const LogLevel LogLevel::error = LogLevel(2);
	const LogLevel LogLevel::fatal = LogLevel(3);
}
