//
//  StringUtils.hpp
//  Bomberman
//
//  Created on 14/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#ifndef __StringUtils_hpp__
#define __StringUtils_hpp__

#include <string>
#include <vector>

namespace Bomberman {
	namespace StringUtils {
		std::vector<std::string> split(std::string str, char separator);
		
		std::string join(std::vector<std::string> strs, char separator);
		
		std::string join(std::vector<std::string> strs, std::string separator);
		
		std::string leftTrim(std::string str);
		
		std::string rightTrim(std::string str);
		
		std::string trim(std::string str);
	}
}

#endif // __StringUtils_hpp__
