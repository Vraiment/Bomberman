//
//  OperatingSystem.cpp
//  Bomberman
//
//  Created on 11/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "OperatingSystem.hpp"

#include <memory>

#if defined(__APPLE__)
#include <dirent.h>
#endif

using namespace std;

namespace Bomberman {
    string getPath(vector<string> dirs) {
        string result;
        
        for (size_t i = 0; i < dirs.size(); ++i) {
            result += dirs[i] + dirSeparator;
        }
        
        return result;
    }
    
    string getPath(vector<string> dirs, string file) {
        return getPath(dirs) + file;
    }
    
    bool listDir(string path, vector<string>& contents) {
        bool result = false;
        
#if defined(__APPLE__)
        DIR *d = opendir(path.c_str());
        if (nullptr != d) {
            shared_ptr<DIR> dir(d, closedir);
            
            // read each entry in the directory
            for (auto ent = readdir(dir.get()); nullptr != ent; ent = readdir(dir.get())) {
                contents.push_back(ent->d_name);
            }
            
            result = true;
        }
#endif
        
        return result;
    }
}
