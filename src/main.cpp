//
//  main.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "CommandFactory.hpp"
#include "CommandQueue.hpp"
#include "Configuration.hpp"
#include "Engine.hpp"
#include "EventListeners/PlayerEvents.hpp"
#include "MainLoop.hpp"
#include "Map/TileMap.hpp"
#include "Map/TileMapLoader.hpp"
#include "Screens/Viewport.hpp"

using namespace Bomberman;
using namespace std;

int main(int argc, char* argv[]) {
	//Standalone objects
	Engine engine;
	Configuration config("config.xml");
	shared_ptr<CommandFactory> commandFactory(new CommandFactory());
	TileMapLoader mapLoader;
	MainLoop loop;
	
	//Dependants objects
	shared_ptr<Viewport> viewport(new Viewport(config.viewportWidth(), config.viewportHeight(), config.viewportTitle()));
	shared_ptr<PlayerEvents> playerEvents(new PlayerEvents(commandFactory, loop.commandQueue()));
	shared_ptr<TileMapBuilder> builder = mapLoader.load("map1.xml");
	shared_ptr<TileMap> tileMap(new TileMap(builder));
	
	commandFactory->setTileMap(tileMap);
	commandFactory->setPlayer(tileMap->player());
	
	viewport->loadTileMap(tileMap);
	viewport->origin() = Coordinate(250, 50);
	
	//Game
	loop.addEventListener(playerEvents);
	loop.addScreen(viewport);
	loop.run();
	
	return 0;
}
