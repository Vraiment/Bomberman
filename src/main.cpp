//
//  main.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include <memory>

// Basic core classes
#include "Core/Engine.hpp"
#include "Core/Log/LogSystem.h"
#include "Core/MainLoop.hpp"
#include "Core/Screen.hpp"
#include "Core/ScreenManager.hpp"
#include "Core/SignalSender.hpp"

// Screen Components
#include "Game/InGameCommandQueue.hpp"
#include "Game/EventListeners/ConsoleEvents.hpp"
#include "Game/EventListeners/PlayerEvents.hpp"
#include "Game/Layers/ConsoleLayer.hpp"
#include "Game/Layers/GameLayer.hpp"
#include "Game/Layers/HowToPlay.hpp"
#include "Game/Layers/HudLayer.hpp"
#include "Game/Layers/LevelListLayer.hpp"
#include "Game/Layers/MainMenuLayer.hpp"
#include "Game/Layers/MapEditor.hpp"
#include "Game/Layers/PauseMenu.hpp"

#include "Game/CommandFactory.hpp"
#include "Game/Configuration.hpp"
#include "Game/Console.hpp"
#include "Game/MapSetter.hpp"
#include "Game/Signal.hpp"

using namespace Bomberman;
using namespace std;

int main(int argc, char* argv[]) {
    try {
        //Standalone objects
        Engine engine;
        Configuration config("config.xml");
        MainLoop loop;
        shared_ptr<Screen> screen(new Screen(config.viewportWidth(), config.viewportHeight(), config.viewportTitle()));
        auto commandFactory = make_shared<CommandFactory>();
        auto console = make_shared<Console>(commandFactory);
        auto mapSetter = make_shared<MapSetter>();
        
        // Screen components
        auto commandQueue = make_shared<InGameCommandQueue>();
        auto consoleEvents = make_shared<ConsoleEvents>();
        auto playerEvents = make_shared<PlayerEvents>();
        auto consoleLayer = make_shared<ConsoleLayer>();
        auto gameLayer = make_shared<GameLayer>();
        auto howToPlay = make_shared<HowToPlay>();
        auto hudLayer = make_shared<HudLayer>();
        auto levelListLayer = make_shared<LevelListLayer>();
        auto mainMenuLayer = make_shared<MainMenuLayer>();
        auto mapEditor = make_shared<MapEditor>();
        auto pauseMenu = make_shared<PauseMenu>();
        
        // Intialize all the screen components
        consoleEvents->setConsole(console);
        playerEvents->setCommandFactory(commandFactory);
        playerEvents->setCommandQueue(commandQueue);
        gameLayer->setSignalSender(screen->getSignalSender());
        howToPlay->setSignalSender(screen->getSignalSender());
        levelListLayer->setSignalSender(screen->getSignalSender());
        levelListLayer->setMapSetter(mapSetter);
        mainMenuLayer->setLoopQuiter(loop.quiter());
        mainMenuLayer->setSignalSender(screen->getSignalSender());
        mapEditor->setLoopQuiter(loop.quiter());
        mapEditor->setSignalSender(screen->getSignalSender());
        pauseMenu->setLoopQuiter(loop.quiter());
        pauseMenu->setSignalSender(screen->getSignalSender());
        
        // Load everything
        consoleLayer->load(screen->renderer());
        gameLayer->load(screen->renderer());
        howToPlay->load(screen->renderer());
        hudLayer->load(screen->renderer());
        levelListLayer->load(screen->renderer());
        mainMenuLayer->load(screen->renderer());
        mapEditor->load(screen->renderer());
        pauseMenu->load(screen->renderer());
        
        // Register everything
        auto screenManager = screen->getScreenManager();
        
        screenManager->addUpdatable(commandQueue);
        screenManager->addSignalHandler(commandQueue);
        
        screenManager->addEventListener(consoleEvents);
        screenManager->addSignalHandler(consoleEvents);
        
        screenManager->addEventListener(playerEvents);
        screenManager->addSignalHandler(playerEvents);
        
        screenManager->addEventListener(gameLayer);
        screenManager->addDrawable(gameLayer);
        screenManager->addUpdatable(gameLayer);
        screenManager->addSignalHandler(gameLayer);
        
        screenManager->addEventListener(howToPlay);
        screenManager->addDrawable(howToPlay);
        screenManager->addUpdatable(howToPlay);
        screenManager->addSignalHandler(howToPlay);
        
        screenManager->addDrawable(hudLayer);
        screenManager->addSignalHandler(hudLayer);
        
        screenManager->addDrawable(consoleLayer);
        screenManager->addUpdatable(consoleLayer);
        screenManager->addSignalHandler(consoleLayer);
        Log::get().addLogger(consoleLayer);
        
        screenManager->addEventListener(levelListLayer);
        screenManager->addDrawable(levelListLayer);
        screenManager->addUpdatable(levelListLayer);
        screenManager->addSignalHandler(levelListLayer);
        
        screenManager->addEventListener(mainMenuLayer);
        screenManager->addDrawable(mainMenuLayer);
        screenManager->addUpdatable(mainMenuLayer);
        screenManager->addSignalHandler(mainMenuLayer);
        
        screenManager->addEventListener(mapEditor);
        screenManager->addDrawable(mapEditor);
        screenManager->addUpdatable(mapEditor);
        screenManager->addSignalHandler(mapEditor);
        
        screenManager->addEventListener(pauseMenu);
        screenManager->addDrawable(pauseMenu);
        screenManager->addUpdatable(pauseMenu);
        screenManager->addSignalHandler(pauseMenu);
        
        // Register other stuff
        commandFactory->setConsole(console);
        commandFactory->setLoopQuiter(loop.quiter());
        console->setCommandQueue(commandQueue);
        console->setConsoleLayer(consoleLayer);
        console->setSignalSender(screen->getSignalSender());
        mapSetter->setCommandFactory(commandFactory);
        mapSetter->setGameLayer(gameLayer);
        mapSetter->setHudLayer(hudLayer);
        
        //Game
        loop.addScreen(screen);
        loop.run();
    } catch (exception&) {
        return 1;
    }
    
    return 0;
}
