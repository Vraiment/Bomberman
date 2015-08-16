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
#include "Console.hpp"
#include "Engine.hpp"
#include "EventListeners/ConsoleEvents.hpp"
#include "EventListeners/PlayerEvents.hpp"
#include "Layers/ConsoleLayer.hpp"
#include "Layers/GameLayer.hpp"
#include "Layers/HudLayer.hpp"
#include "MainLoop.hpp"
#include "Map/TileMap.hpp"
#include "Map/TxtTileMapLoader.hpp"
#include "Map/XmlTileMapLoader.hpp"
#include "Screen.hpp"

using namespace Bomberman;
using namespace std;

int main(int argc, char* argv[]) {
	try {
		//Standalone objects
		Engine engine;
		Configuration config("config.xml");
		shared_ptr<CommandFactory> commandFactory(new CommandFactory());
		shared_ptr<GameLayer> gameLayer(new GameLayer());
		shared_ptr<HudLayer> hudLayer(new HudLayer());
		shared_ptr<ConsoleLayer> consoleLayer(new ConsoleLayer());
		TxtTileMapLoader mapLoader;
		MainLoop loop;
	
		//Dependants objects
		shared_ptr<Screen> screen(new Screen(config.viewportWidth(), config.viewportHeight(), config.viewportTitle()));
		shared_ptr<TileMapBuilder> builder = mapLoader.load("map1.txt");
		shared_ptr<TileMap> tileMap(new TileMap(builder));
		shared_ptr<PlayerEvents> playerEvents(new PlayerEvents(commandFactory, loop.commandQueue(), tileMap->player()));
		shared_ptr<Console> console(new Console(commandFactory, loop.commandQueue()));
		shared_ptr<ConsoleEvents> consoleEvents(new ConsoleEvents(console));
	
		commandFactory->setTileMap(tileMap);
		commandFactory->setPlayer(tileMap->player());
		
		hudLayer->loadGraphics(screen->renderer());
		gameLayer->loadGraphics(screen->renderer());
		consoleLayer->loadGraphics(screen->renderer());
		
		gameLayer->setTileMap(tileMap);
		
		screen->addLayer(gameLayer);
		screen->addLayer(hudLayer);
		screen->addLayer(consoleLayer);
		
		//Game
		loop.addEventListener(playerEvents);
		loop.addEventListener(consoleEvents);
		loop.addScreen(screen);
		loop.run();
	} catch (exception& e) {
#ifdef DEBUG
		throw e;
#endif
		
		return 1;
	}
	
	return 0;
}
