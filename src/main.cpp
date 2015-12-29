//
//  main.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "Game/Configuration.hpp"
#include "Core/Engine.hpp"
#include "Core/EventListenerQueue.hpp"
#include "Game/EventListeners/ConsoleEvents.hpp"
#include "Game/EventListeners/MenuEventListener.hpp"
#include "Game/EventListeners/PlayerEvents.hpp"
#include "Core/LayerQueue.hpp"
#include "Game/Layers/ConsoleLayer.hpp"
#include "Game/Layers/GameLayer.hpp"
#include "Game/Layers/HudLayer.hpp"
#include "Game/Layers/MainMenuLayer.hpp"
#include "Core/Log/LogSystem.h"
#include "Core/MainLoop.hpp"
#include "Game/Map/TileMap.hpp"
#include "Game/Map/TxtTileMapLoader.hpp"
#include "Game/Map/XmlTileMapLoader.hpp"
#include "Core/Screen.hpp"

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
        mainMenuLayer->setLoopQuiter(loop.quiter());
        mainMenuLayer->setEventListenerQueue(loop.getEventListenerQueue());
        mainMenuLayer->setLayerQueue(screen->getLayerQueue());
        
        screen->getLayerQueue()->addLayer(mainMenuLayer);
        loop.getEventListenerQueue()->addEventListener(mainMenuEvents);
        
        //Game
        loop.addScreen(screen);
        loop.run();
    } catch (exception&) {
        return 1;
    }
    
    return 0;
}
