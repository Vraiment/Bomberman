//
//  MainMenuLayer.cpp
//  Bomberman
//
//  Created on 27/16/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "MainMenuLayer.hpp"

#include <SDL2/SDL.h>

#include "../CommandFactory.hpp"
#include "../Console.hpp"
#include "../EventListeners/ConsoleEvents.hpp"
#include "../EventListeners/PlayerEvents.hpp"
#include "../../Core/Font.hpp"
#include "../Layers/ConsoleLayer.hpp"
#include "../Layers/GameLayer.hpp"
#include "../Layers/HudLayer.hpp"
#include "../../Core/LoopQuiter.hpp"
#include "../Map/TileMap.hpp"
#include "../Map/TxtTileMapLoader.hpp"
#include "../../Core/Log/LogSystem.h"
#include "../../Core/ScreenManager.hpp"
#include "../Director.hpp"

using namespace std;

namespace Bomberman {
    const int MainMenuLayer::ENTRIES_SPACING = 100;
    
    MainMenuLayer::MainMenuLayer() : selected(nullptr), shouldStartGame(false), shouldExit(false) {
        
    }
    
    void MainMenuLayer::listenEvent(SDL_Event event) {
        Coordinate position;
        
        if (SDL_MOUSEBUTTONDOWN == event.type) {
            SDL_GetMouseState(&position.i, &position.j);
            
            click(position);
        } else if (SDL_MOUSEMOTION == event.type) {
            SDL_GetMouseState(&position.i, &position.j);
            
            select(position);
        }
    }
    
    void MainMenuLayer::update() {
        if (shouldStartGame) {
            if (this->director.expired()) {
                Log::get() << "Invalid Director for MainMenuLayer" << LogLevel::error;
            } else {
                auto director = this->director.lock();
                
                director->showLevelList();
            }
        } else if (shouldExit) {
            if (this->loopQuiter.expired()) {
                Log::get() << "Invalid LoopQuiter for MainMenuLayer" << LogLevel::error;
            } else {
                auto loopQuiter = this->loopQuiter.lock();
                
                loopQuiter->quitLoop();
            }
        }
    }
    
    void MainMenuLayer::postUpdate() {
        shouldStartGame = false;
        shouldExit = false;
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
            
            startGame.setColor(Color::BLUE);
            selected =  &startGame;
        } else if (exit.rectangle().contains(position)) {
            if (selected && &exit != selected) {
                selected->setColor(Color::WHITE);
            }
            
            exit.setColor(Color::BLUE);
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
    
    void MainMenuLayer::setDirector(weak_ptr<Director> Director) {
        this->director = Director;
    }
    
    void MainMenuLayer::setLoopQuiter(weak_ptr<LoopQuiter> loopQuiter) {
        this->loopQuiter = loopQuiter;
    }
    
    void MainMenuLayer::load(shared_ptr<SDL_Renderer> renderer) {
        Font font("PressStart2P.ttf", 50, renderer);
        
        startGame = font.write("Start Game");
        exit = font.write("Exit");
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
