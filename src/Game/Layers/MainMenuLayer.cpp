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
#include "../../Core/Utils/PointerUtils.hpp"

using namespace std;

namespace Bomberman {
    template <typename T>
    bool _lock(weak_ptr<T> in, shared_ptr<T>& out, string component) {
        bool result = lockWeakPointer(in, out);
        
        if (!result) {
            Log::get() << "No " << component << " for MainMenuLayer" << LogLevel::error;
        }
        
        return result;
    }
    
    const int MainMenuLayer::ENTRIES_SPACING = 100;
    
    MainMenuLayer::MainMenuLayer() : shouldStartGame(false), shouldExit(false), clicking(false), selectedEntry(-1) {
        
    }
    
    void MainMenuLayer::listenEvent(SDL_Event event) {
        Coordinate position;
        
        if (SDL_MOUSEBUTTONDOWN == event.type) {
            SDL_GetMouseState(&position.i, &position.j);
            
            clicking = true;
            select(position);
        } else if (SDL_MOUSEBUTTONUP == event.type && clicking) {
            clicking = false;
            
            pushSelectedButton();
        } else if (SDL_MOUSEMOTION == event.type) {
            SDL_GetMouseState(&position.i, &position.j);
            
            select(position);
        } else if (SDL_KEYUP == event.type) {
            auto keySym = event.key.keysym.sym;
            
            if (SDLK_UP == keySym && !clicking) {
                select(selectedEntry - 1);
            } else if (SDLK_DOWN == keySym && !clicking) {
                select(selectedEntry + 1);
            } else if (SDLK_RETURN == keySym && !clicking) {
                pushSelectedButton();
            }
        }
    }
    
    void MainMenuLayer::update() {
        if (shouldStartGame) {
            shared_ptr<Director> director;
            if (_lock(this->director, director, "Director")) {
                director->showLevelList();
            }
        } else if (shouldExit) {
            shared_ptr<LoopQuiter> loopQuiter;
            if (_lock(this->loopQuiter, loopQuiter, "LoopQuiter")) {
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
    
    void MainMenuLayer::select(int entry) {
        if (selectedEntry >= 0 && selectedEntry < menuEntries.size()) {
            menuEntries[selectedEntry]->setColor(Color::WHITE);
            selectedEntry = -1;
        }
        
        if (entry >= 0 && entry < menuEntries.size()) {
            selectedEntry = entry;
            menuEntries[selectedEntry]->setColor(Color::BLUE);
        }
    }
    
    void MainMenuLayer::select(Coordinate position) {
        for (int n = 0; n < menuEntries.size(); ++n) {
            if (menuEntries[n]->rectangle().contains(position)) {
                select(n);
                return;
            }
        }
        
        select(-1);
    }
    
    void MainMenuLayer::pushSelectedButton() {
        if (0 == selectedEntry) {
            shouldStartGame = true;
        } else if (1 == selectedEntry) {
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
        
        menuEntries.push_back(&startGame);
        menuEntries.push_back(&exit);
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
