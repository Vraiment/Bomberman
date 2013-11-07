//
//  Engine.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Engine.hpp"

#include "Screen.hpp"

#include <SDL2/SDL.h>
#include <sstream>

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif //__APPLE__

using namespace std;

namespace Bomberman {
	Engine::Engine() {
		SDL_Init(SDL_INIT_EVERYTHING);
		
		setPath();
	}
	
	Engine::~Engine() {
		SDL_Quit();
	}
	
	void Engine::setPath() {
#ifdef __APPLE__
		char path[PATH_MAX];
		CFURLRef res = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
		CFURLGetFileSystemRepresentation(res, TRUE, (UInt8 *)path, PATH_MAX);
		CFRelease(res);
		chdir(path);
#endif
	}
}
