//
//  OperatingSystem.cpp
//  Bomberman
//
//  Created on 11/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "OperatingSystem.hpp"

using namespace std;

namespace Bomberman {
	string getPath(vector<string> dirs) {
		string result;
		
		for (int i = 0; i < dirs.size(); ++i) {
			result += dirs[i] + dirSeparator;
		}
		
		return result;
	}
	
	string getPath(vector<string> dirs, string file) {
		return getPath(dirs) + file;
	}
}
