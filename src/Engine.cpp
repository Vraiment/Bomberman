//
//  Engine.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Engine.hpp"

#include <SDL2/SDL.h>
#include <sstream>

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif //__APPLE__

using namespace std;

namespace Bomberman {
	void destroyRenderer(SDL_Renderer *renderer) {
		SDL_DestroyRenderer(renderer);
	}
	
	void destroyWindow(SDL_Window *window) {
		SDL_DestroyWindow(window);
	}
	
	Engine::Engine() : window(nullptr), renderer(nullptr) {
		SDL_Init(SDL_INIT_EVERYTHING);
		
		setPath();
		
		configuration = Configuration("config.xml");
		setLoggers();
		
		SDL_Window *w = SDL_CreateWindow(configuration.viewportTitle().c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, configuration.viewportWidth(), configuration.viewportHeight(), SDL_WINDOW_SHOWN);
		if (w == nullptr) {
			stringstream error;
			error << "Error creating the viewport. (" << SDL_GetError() << ").";
			
			Logger::log(error.str(), LogLevel::fatal);
		}
		
		SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (r == nullptr) {
			stringstream error;
			error << "Error creating the renderer. (" << SDL_GetError() << ").";
			
			destroyWindow(w);
			Logger::log(error.str(), LogLevel::fatal);
		}
		
		window.reset(w, destroyWindow);
		renderer.reset(r, destroyRenderer);
	}
	
	Engine::~Engine() {
		SDL_Quit();
	}
	
	Renderer Engine::getRenderer() const {
		return renderer;
	}
	
	Configuration Engine::getConfiguration() const {
		return configuration;
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
	
	void Engine::setLoggers() {
		vector<string> loggers = configuration.loggers();
		
		for (int n = 0; n < loggers.size(); ++n) {
			Logger::log("Unkown logger \"" + loggers[n] + "\" found in configuration file.", LogLevel::warning);
		}
	}
}
