//
//  MainMenuLayer.cpp
//  Bomberman
//
//  Created on 27/16/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "MainMenuLayer.hpp"

#include "../CommandFactory.hpp"
#include "../Console.hpp"
#include "../../Core/EventListenerQueue.hpp"
#include "../EventListeners/ConsoleEvents.hpp"
#include "../EventListeners/PlayerEvents.hpp"
#include "../../Core/Font.hpp"
#include "../../Core/LayerQueue.hpp"
#include "../Layers/ConsoleLayer.hpp"
#include "../Layers/GameLayer.hpp"
#include "../Layers/HudLayer.hpp"
#include "../../Core/LoopQuiter.hpp"
#include "../Map/TileMap.hpp"
#include "../Map/TxtTileMapLoader.hpp"
#include "../../Core/Log/LogSystem.h"

using namespace std;

namespace Bomberman {
    shared_ptr<TileMap> loadTileMap() {
        TxtTileMapLoader mapLoader;
        shared_ptr<TileMapBuilder> builder = mapLoader.load("map1.txt");
        shared_ptr<TileMap> tileMap(new TileMap(builder));
        
        return tileMap;
    }
    
    const int MainMenuLayer::ENTRIES_SPACING = 100;
    
    MainMenuLayer::MainMenuLayer() : selected(nullptr), shouldStartGame(false) {
        
    }
    
    void MainMenuLayer::update() {
        if (shouldStartGame) {
            auto tileMap = loadTileMap();
            
            shared_ptr<GameLayer> gameLayer(new GameLayer());
            gameLayer->load(renderer);
            gameLayer->setTileMap(tileMap);
            gameLayer->getCommandFactory()->setLoopQuiter(loopQuiter);
            
            auto commandFactory = gameLayer->getCommandFactory();
            auto commandQueue = gameLayer->getCommandQueue();
            
            shared_ptr<PlayerEvents> playerEvents(new PlayerEvents(commandFactory, commandQueue, tileMap->player()));
            eventListenerQueue->addEventListener(playerEvents);
            
            shared_ptr<ConsoleLayer> consoleLayer(new ConsoleLayer());
            consoleLayer->load(renderer);
            
            shared_ptr<Console> console(new Console(commandFactory, commandQueue, consoleLayer, gameLayer, playerEvents));
            
            shared_ptr<ConsoleEvents> consoleEvents(new ConsoleEvents(console));
            eventListenerQueue->addEventListener(consoleEvents);
            
            shared_ptr<HudLayer> hudLayer(new HudLayer());
            hudLayer->load(renderer);
            
            layerQueue->addLayer(gameLayer);
            layerQueue->addLayer(hudLayer);
            layerQueue->addLayer(consoleLayer);
            
            playerEvents->addInGameLayer(gameLayer);
            playerEvents->addInGameLayer(hudLayer);
            playerEvents->addInGameLayer(consoleLayer);
            playerEvents->setConsoleEventListener(consoleEvents);
            playerEvents->setMainMenuLayer(shared_from_this());
            
            Log::get().addLogger(consoleLayer);
            
            shouldStartGame = false;
            shouldDraw(false);
            shouldUpdate(false);
        } else if (shouldExit) {
            loopQuiter->quitLoop();
        }
    }
    
    void MainMenuLayer::draw() {
        startGame.draw();
        exit.draw();
    }
    
    void MainMenuLayer::select(Coordinate position) {
        if (startGame.rectangle().contains(position)) {
            if (selected && &startGame != selected) {
                selected->setColor(Color::WHITE);
            }
            
            startGame.setColor(Color::RED);
            selected =  &startGame;
        } else if (exit.rectangle().contains(position)) {
            if (selected && &exit != selected) {
                selected->setColor(Color::WHITE);
            }
            
            exit.setColor(Color::RED);
            selected = &exit;
        } else if (selected) {
            selected->setColor(Color::WHITE);
            selected = nullptr;
        }
    }
    
    void MainMenuLayer::click(Coordinate position) {
        if (startGame.rectangle().contains(position)) {
            shouldStartGame = true;
        } else if (exit.rectangle().contains(position)) {
            shouldExit = true;
        }
    }
    
    void MainMenuLayer::setEventListenerQueue(shared_ptr<EventListenerQueue> eventListenerQueue) {
        this->eventListenerQueue = eventListenerQueue;
    }
    
    void MainMenuLayer::setLayerQueue(shared_ptr<LayerQueue> layerQueue) {
        this->layerQueue = layerQueue;
    }
    
    void MainMenuLayer::setLoopQuiter(shared_ptr<LoopQuiter> loopQuiter) {
        this->loopQuiter = loopQuiter;
    }
    
    void MainMenuLayer::load(shared_ptr<SDL_Renderer> renderer) {
        Font font("PressStart2P.ttf", 50, renderer);
        
        startGame = font.write("Start Game");
        exit = font.write("Exit");
        
        this->renderer = renderer;
    }
    
    void MainMenuLayer::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
        startGame.rectangle() = Coordinate::ZERO;
        exit.rectangle() = Coordinate::ZERO;
        
        int totalHeight = startGame.rectangle().height + exit.rectangle().height;
        totalHeight += ENTRIES_SPACING * (1); // Spacing * menu entries less one
        
        startGame.rectangle().i = newSize.widthCenter() - startGame.rectangle().widthCenter();
        startGame.rectangle().j = newSize.heightCenter() - (totalHeight / 2);
        
        exit.rectangle().i = newSize.widthCenter() - exit.rectangle().widthCenter();
        exit.rectangle().j = startGame.rectangle().bottom() + ENTRIES_SPACING;
    }
}
