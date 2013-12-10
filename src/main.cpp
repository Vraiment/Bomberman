//
//  main.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "Configuration.hpp"
#include "Engine.hpp"
#include "MainLoop.hpp"
#include "Screens/Viewport.hpp"
#include "TileMap.hpp"

using namespace Bomberman;
using namespace std;

int main(int argc, char* argv[]) {
	Engine engine;
	
	Configuration config("config.xml");
	shared_ptr<Viewport> viewport(new Viewport(config.viewportWidth(), config.viewportHeight(), config.viewportTitle()));
	shared_ptr<TileMap> tileMap(new TileMap("map1.xml"));
	
	viewport->loadTileMap(tileMap);
	viewport->origin() = Coordinate(250, 50);
	
	MainLoop loop;
	loop.addScreen(viewport);
	loop.run();
	
	return 0;
}
