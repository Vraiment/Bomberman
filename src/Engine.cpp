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
	void destroyRenderer(SDL_Renderer *renderer) {
		SDL_DestroyRenderer(renderer);
	}
	
	void destroyWindow(SDL_Window *window) {
		SDL_DestroyWindow(window);
	}
	
	Engine::Engine() : window(nullptr), renderer(nullptr) {
		SDL_Init(SDL_INIT_EVERYTHING);
		
		SDL_Window *w = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
		SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		
		renderer.reset(r, destroyRenderer);
		window.reset(w, destroyWindow);
		
		setPath();
	}
	
	Engine::~Engine() {
		SDL_Quit();
	}
	
	Renderer Engine::getRenderer() const {
		return renderer;
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
