//
//  main.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include <SDL2/SDL.h>

#include "Engine.hpp"
#include "Configuration.hpp"
#include "TileMapBuilder.hpp"
#include "MainLoop.hpp"
#include "EmptyScreen.hpp"

using namespace Bomberman;
using namespace std;

void setLoggers(Configuration configuration) {
	vector<string> loggers = configuration.loggers();
	
	for (int n = 0; n < loggers.size(); ++n) {
		Logger::log("Unkown logger \"" + loggers[n] + "\" found in configuration file.", LogLevel::warning);
	}
}

int main(int argc, char* argv[]) {
	Engine engine;
	Configuration config("config.xml");
	TileMapBuilder builder("map1.xml");
	MainLoop loop;
	
	shared_ptr<Screen> emptyScreen(new EmptyScreen(0, 0));
	loop.addScreen(emptyScreen);
	
	loop.run();
	
	return 0;
}
