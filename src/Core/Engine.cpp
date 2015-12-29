//
//  Engine.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Engine.hpp"

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif //__APPLE__
#ifdef _WIN64
#include <Windows.h>
#include <PathCch.h>
#endif //_WIN64
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <cstdlib>
#include <ctime>
#include <string>

#include "Constants.hpp"
#include "Log/LogSystem.h"
#include "Utils/Exception.hpp"
#include "Utils/OperatingSystem.hpp"

using namespace Bomberman::Constants;
using namespace std;

namespace Bomberman {
    Engine::Engine() {
        SDL_Init(SDL_INIT_EVERYTHING);
        
        TTF_Init();
        
        setPath();
        
        srand(static_cast<unsigned>(time(0)));
    }
    
    Engine::~Engine() {
        SDL_Quit();
    }
    
    void Engine::setPath() {
#if defined(__APPLE__)
        char path[PATH_MAX];
        CFURLRef res = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
        CFURLGetFileSystemRepresentation(res, TRUE, (UInt8 *)path, PATH_MAX);
        CFRelease(res);
        chdir(path);
#elif defined(_WIN64)
        char exePath[MAX_PATH];
        int result;
        
        result = GetModuleFileNameA(NULL, exePath, MAX_PATH);

        if (ERROR_INSUFFICIENT_BUFFER == result || 0 == result) {
            Log::get() << "Could not get executable path" << NativeOperationException();
        }

        string resourcesPath(exePath);
        size_t separatorPos = resourcesPath.rfind(dirSeparator);

        if (string::npos == separatorPos) {
            Log::get() << "Executable path is incorrect" << NativeOperationException();
        }

        resourcesPath.erase(separatorPos + 1); // Do not delete the '\'
        resourcesPath.append(DIR_RESOURCES);

        if (!SetCurrentDirectoryA(resourcesPath.c_str())) {
            Log::get() << "Could not set resources path" << NativeOperationException();
        }
#endif
    }
}
