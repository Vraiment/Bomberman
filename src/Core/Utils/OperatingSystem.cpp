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
#if defined(_WIN64)
#include <Windows.h>
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
                string entName = ent->d_name;
                
                if ("." != entName && ".." != entName) {
                    contents.push_back(entName);
                }
            }
            
            result = true;
        }
#elif defined(_WIN64)
        path = getPath({ path }, "*");

        HANDLE directoryHandle = INVALID_HANDLE_VALUE;
        WIN32_FIND_DATAA data;

        directoryHandle = FindFirstFileA(path.c_str(), &data);
        if (INVALID_HANDLE_VALUE != directoryHandle) {
            do {
                contents.push_back(data.cFileName);
            } while (FindNextFileA(directoryHandle, &data));

            result = true;
        }
#endif
        
        return result;
    }
}
