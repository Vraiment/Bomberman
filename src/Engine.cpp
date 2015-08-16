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
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <cstdlib>
#include <ctime>

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
#ifdef __APPLE__
		char path[PATH_MAX];
		CFURLRef res = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
		CFURLGetFileSystemRepresentation(res, TRUE, (UInt8 *)path, PATH_MAX);
		CFRelease(res);
		chdir(path);
#endif
	}
}
