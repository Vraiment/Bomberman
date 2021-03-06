//
//  MainLoop.cpp
//  Bomberman
//
//  Created on 02/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "MainLoop.hpp"

#include <SDL2/SDL.h>

#include "CommandQueue.hpp"
#include "EventListener.hpp"
#include "Log/Log.hpp"
#include "Log/LogLevel.hpp"
#include "LoopQuiter.hpp"
#include "Screen.hpp"

using namespace std;

namespace Bomberman {
    MainLoop::MainLoop() : _quiter(new LoopQuiter()) {
        
    }
    
    MainLoop::~MainLoop() {
        
    }
    
    shared_ptr<LoopQuiter> MainLoop::quiter() {
        return _quiter;
    }
    
    void MainLoop::run() {
        if (screens.empty()) {
            Log::get() << "Main loop is empty." << LogLevel::error;
            return;
        }
        
        SDL_Event event;
        
        while (!_quiter->shouldQuit()) {
            for (auto screen : screens) {
                screen->sendSignal();
            }
            
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    _quiter->quitLoop();
                }
                
                for (auto screen : screens) {
                    screen->listenEvent(event);
                }
            }
            
            for (auto it = screens.begin(); it != screens.end(); ++it) {
                SDL_RenderClear((*it)->renderer().get());
                (*it)->draw();
                SDL_RenderPresent((*it)->renderer().get());
            }
            
            for (auto it = screens.begin(); it != screens.end(); ++it) {
                (*it)->update();
            }
            
            for (auto screen : screens) {
                screen->postUpdate();
            }
            
            for (auto screen : screens) {
                screen->refreshScreen();
            }
        }
    }
    
    void MainLoop::addScreen(shared_ptr<Screen> screen) {
        if (hasScreen(screen)) {
            Log::get() << "Trying to insert existing screen." << LogLevel::error;
            return;
        }
        
        Log::get() << "Inserting screen." << LogLevel::info;
        screens.push_back(screen);
    }
    
    void MainLoop::removeScreen(shared_ptr<Screen> screen) {
        if (!hasScreen(screen)) {
            Log::get() << "Trying unexisting screen." << LogLevel::error;
            return;
        }
        
        Log::get() << "Removing screen." << LogLevel::info;
        screens.remove(screen);
    }
    
    bool MainLoop::hasScreen(shared_ptr<Screen> screen) {
        for (auto it = screens.begin(); it != screens.end(); ++it) {
            if (*it == screen) {
                return true;
            }
        }
        
        return false;
    }
}
