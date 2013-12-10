//
//  LogLevel.cpp
//  Bomberman
//
//  Created on 13/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "LogLevel.hpp"

using namespace std;

namespace Bomberman {
	LogLevel::LogLevel(int type, string str) : type(type), str(str) {
		
	}
	
	string LogLevel::toString() const {
		return str;
	}
	
	bool LogLevel::operator==(const LogLevel& other) const {
		return type == other.type;
	}
	
	bool LogLevel::operator!=(const LogLevel& other) const {
		return !(*this == other);
	}
	
	const LogLevel LogLevel::info = LogLevel(0, "info");
	const LogLevel LogLevel::warning = LogLevel(1, "warning");
	const LogLevel LogLevel::error = LogLevel(2, "error");
	const LogLevel LogLevel::fatal = LogLevel(3, "fatal");
}
