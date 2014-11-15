//
//  StringUtils.cpp
//  Bomberman
//
//  Created on 14/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#include "StringUtils.hpp"

#include <sstream>

using namespace std;

namespace Bomberman {
	namespace StringUtils {
		vector<string> split(string str, char separator) {
			vector<string> result;
			stringstream buffer;
			
			for (int n = 0; n < str.length(); ++n) {
				if (str[n] == separator) {
					result.push_back(buffer.str());
					
					buffer.str(string());
					buffer.clear();
				} else {
					buffer << str[n];
				}
			}

			if (!str.empty()) {
				result.push_back(buffer.str());
			}
			
			return result;
		}
		
		string join(vector<string> strs, char separator) {
			return join(strs, string(1, separator));
		}
		
		string join(vector<string> strs, std::string separator) {
			stringstream buffer;
			
			for (int n = 0; n < strs.size(); ++n) {
				if (n != 0) {
					buffer << separator;
				}
				
				buffer << strs[n];
			}
			
			return buffer.str();
		}
	}
}
