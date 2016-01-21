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
#include "../../Core/Utils/PointerUtils.hpp"
#include "../Signal.hpp"
#include "../../Core/SignalSender.hpp"

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
    
    MainMenuLayer::MainMenuLayer() : clicking(false), selectedEntry(-1), clickedEntry(-1) {
        
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
        if (0 == clickedEntry) {
            shared_ptr<SignalSender> signalSender;
            if (_lock(this->signalSender, signalSender, "Director")) {
                signalSender->sendSignal(Signal::LevelList);
            }
        } else if (1 == clickedEntry) {
            shared_ptr<SignalSender> signalSender;
            if (_lock(this->signalSender, signalSender, "Director")) {
                signalSender->sendSignal(Signal::ShowTutorial);
            }
        } else if (2 == clickedEntry) {
            shared_ptr<SignalSender> signalSender;
            if (_lock(this->signalSender, signalSender, "SignalSender")) {
                signalSender->sendSignal(Signal::MapEditor);
            }
        } else if (3 == clickedEntry) {
            shared_ptr<LoopQuiter> loopQuiter;
            if (_lock(this->loopQuiter, loopQuiter, "LoopQuiter")) {
                loopQuiter->quitLoop();
            }
        }
    }
    
    void MainMenuLayer::postUpdate() {
        clickedEntry = -1;
    }
    
    void MainMenuLayer::handleSignal(Signal signal) {
        if (Signal::MainMenu == signal) {
            EventListener::enable();
            Drawable::enable();
            Updatable::enable();
            
            // select nothing
            Coordinate position;
            SDL_GetMouseState(&position.i, &position.j);
            select(position);
        } else {
            EventListener::disable();
            Drawable::disable();
            Updatable::disable();
        }
    }
    
    void MainMenuLayer::draw() {
        for (auto entry : menuEntries) {
            entry.draw();
        }
    }
    
    void MainMenuLayer::select(int entry) {
        if (selectedEntry >= 0 && selectedEntry < menuEntries.size()) {
            menuEntries[selectedEntry].setColor(Color::WHITE);
            selectedEntry = -1;
        }
        
        if (entry >= 0 && entry < menuEntries.size()) {
            selectedEntry = entry;
            menuEntries[selectedEntry].setColor(Color::BLUE);
        }
    }
    
    void MainMenuLayer::select(Coordinate position) {
        for (int n = 0; n < menuEntries.size(); ++n) {
            if (menuEntries[n].rectangle().contains(position)) {
                select(n);
                return;
            }
        }
        
        select(-1);
    }
    
    void MainMenuLayer::pushSelectedButton() {
        clickedEntry = selectedEntry;
    }
    
    void MainMenuLayer::setSignalSender(weak_ptr<SignalSender> signalSender) {
        this->signalSender = signalSender;
    }
    
    void MainMenuLayer::setLoopQuiter(weak_ptr<LoopQuiter> loopQuiter) {
        this->loopQuiter = loopQuiter;
    }
    
    void MainMenuLayer::load(shared_ptr<SDL_Renderer> renderer) {
        Font font("PressStart2P.ttf", 50, renderer);
        
        menuEntries.push_back(font.write("Start Game"));
        menuEntries.push_back(font.write("How to play"));
        menuEntries.push_back(font.write("Map builder"));
        menuEntries.push_back(font.write("Exit"));
    }
    
    void MainMenuLayer::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
        if (!menuEntries.empty()) {
            int totalHeight = ENTRIES_SPACING * static_cast<int>(menuEntries.size() - 1);
            for (auto entry : menuEntries) {
                totalHeight += entry.rectangle().height;
            }
            
            auto entry = menuEntries.begin();
            entry->rectangle().i = newSize.widthCenter() - entry->rectangle().widthCenter();
            entry->rectangle().j = newSize.heightCenter() - (totalHeight / 2);
            
            for (auto prevEntry = menuEntries.begin(); ++entry != menuEntries.end(); ++prevEntry) {
                entry->rectangle().i = newSize.widthCenter() - entry->rectangle().widthCenter();
                entry->rectangle().j = prevEntry->rectangle().bottom() + ENTRIES_SPACING;
            }
        }
        
        shared_ptr<SignalSender> signalSender;
        if (_lock(this->signalSender, signalSender, "SignalSender")) {
            signalSender->sendSignal(Signal::MainMenu); // Egotistical jerk
        }
    }
}
