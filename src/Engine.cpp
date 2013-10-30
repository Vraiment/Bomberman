//
//  Engine.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Engine.hpp"

#include <SDL2/SDL.h>

#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif //__APPLE__

namespace Bomberman {
	Engine::Engine() {
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		
		setPath();
	}
	
	Engine::~Engine() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
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
