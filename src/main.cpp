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
#include "EventListeners/MenuEventListener.hpp"
#include "EventListeners/PlayerEvents.hpp"
#include "Layers/ConsoleLayer.hpp"
#include "Layers/GameLayer.hpp"
#include "Layers/HudLayer.hpp"
#include "Layers/MainMenuLayer.hpp"
#include "Log/LogSystem.h"
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
        shared_ptr<MainMenuLayer> mainMenuLayer(new MainMenuLayer());
        MainLoop loop;
        
        //Dependants objects
        shared_ptr<Screen> screen(new Screen(config.viewportWidth(), config.viewportHeight(), config.viewportTitle()));
        shared_ptr<MenuEventListener> mainMenuEvents(new MenuEventListener(mainMenuLayer));
        
        mainMenuLayer->load(screen->renderer());
        
        screen->addLayer(mainMenuLayer);
        
        //Game
        loop.addEventListener(mainMenuEvents);
        loop.addScreen(screen);
        loop.run();
    } catch (exception&) {
        return 1;
    }
    
    return 0;
}
