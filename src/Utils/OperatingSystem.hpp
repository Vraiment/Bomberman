//
//  OperatingSystem.hpp
//  Bomberman
//
//  Created on 11/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __OperatingSystem__hpp__
#define __OperatingSystem__hpp__

#include <string>
#include <vector>

namespace Bomberman {
    
#ifdef __APPLE__
    const char dirSeparator = '/';
#elif defined(_WIN64)
    const char dirSeparator = '\\';
#endif
    
    std::string getPath(std::vector<std::string> dirs);
    std::string getPath(std::vector<std::string> dirs, std::string file);
}

#endif //__OperatingSystem__hpp__
