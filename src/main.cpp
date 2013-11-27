//
//  main.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "Engine.hpp"
#include "Configuration.hpp"
#include "TileMap.hpp"
#include "MainLoop.hpp"
#include "Viewport.hpp"
#include "EmptyScreen.hpp"
#include "Log.hpp"

using namespace Bomberman;
using namespace std;

void setLoggers(Configuration configuration) {
	vector<string> loggers = configuration.loggers();
	
	for (int n = 0; n < loggers.size(); ++n) {
		Log::get() << "Unkown logger \"" << loggers[n] << "\" found in configuration file." << LogLevel::warning;
	}
}

void test() {
	shared_ptr<SDL_Window> w;
	shared_ptr<SDL_Renderer> r;
	shared_ptr<SDL_Texture> t1, t2;
	
	w.reset(SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN), [] (SDL_Window *w1) {
		SDL_DestroyWindow(w1);
	});
	
	r.reset(SDL_CreateRenderer(w.get(), -1, SDL_RENDERER_ACCELERATED), [] (SDL_Renderer *r1) {
		SDL_DestroyRenderer(r1);
	});
	
	t1.reset(IMG_LoadTexture(r.get(), "tile0.png"), [] (SDL_Texture *t) {
		SDL_DestroyTexture(t);
	});
	
	t2.reset(IMG_LoadTexture(r.get(), "tile1.png"), [] (SDL_Texture *t) {
		SDL_DestroyTexture(t);
	});
	
	bool quit = false;
	SDL_Event e;
	SDL_Rect size1, size2;
	
	size1.x = size1.y = 0;
	size1.w = size1.h = 40;
	
	size2.x = size2.y = 100;
	size2.w = size2.h = 40;
	
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		
		SDL_RenderClear(r.get());
		
		SDL_RenderCopy(r.get(), t1.get(), nullptr, &size1);
		SDL_RenderCopy(r.get(), t2.get(), nullptr, &size2);
		
		SDL_RenderPresent(r.get());
	}
}

int main(int argc, char* argv[]) {
	Engine engine;
	
	//test();
	
	Configuration config("config.xml");
	shared_ptr<TileMap> tileMap(new TileMap("map1.xml"));
	
	shared_ptr<Viewport> viewport(new Viewport(config.viewportWidth(), config.viewportHeight(), config.viewportTitle()));
	
	viewport->loadTileMap(tileMap);
	
	MainLoop loop;
	loop.addScreen(viewport);
	loop.run();
	
	return 0;
}
