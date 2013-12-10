//
//  LogLevel.hpp
//  Bomberman
//
//  Created on 13/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __LogLevel__hpp__
#define __LogLevel__hpp__

#include <string>

namespace Bomberman {
	class LogLevel {
	public:
		static const LogLevel info;
		static const LogLevel warning;
		static const LogLevel error;
		static const LogLevel fatal;
		
		std::string toString() const;
		
		bool operator==(const LogLevel& other) const;
		bool operator!=(const LogLevel& other) const;
		
	private:
		LogLevel(int type, std::string str);
		int type;
		std::string str;
	};
}

#endif //__LogLevel__hpp__
