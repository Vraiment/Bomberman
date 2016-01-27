//
//  MapEditor.cpp
//  Bomberman
//
//  Created on 21/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#include "MapEditor.hpp"

#include <functional>
#include <SDL2/SDL.h>
#include <string>

#include "../../Core/Font.hpp"
#include "../../Core/Log/LogSystem.h"
#include "../../Core/LoopQuiter.hpp"
#include "../../Core/Texture.hpp"
#include "../../Core/SignalSender.hpp"
#include "../../Core/Utils/PointerUtils.hpp"

#include "../Signal.hpp"

using namespace std;

namespace Bomberman {
    template <typename T>
    bool _lock(weak_ptr<T> in, shared_ptr<T>& out, string component) {
        bool result = lockWeakPointer(in, out);
        
        if (!result) {
            Log::get() << "No " << component << " for MapEditor" << LogLevel::error;
        }
        
        return result;
    }
    
    MapEditor::MapEditor() : clicked(false), mouseMoved(false), lCtrl(false), rCtrl(false) {
        
    }
    
    MapEditor::~MapEditor() {
        
    }
    
    void MapEditor::draw() {
        if (!tileMap) {
            noMap.draw();
            return;
        }
    }
    
    void MapEditor::listenEvent(SDL_Event event) {
        if (SDL_KEYUP == event.type) {
            auto keysym = event.key.keysym.sym;
            
            if (SDLK_ESCAPE == keysym) {
                shared_ptr<SignalSender> signalSender;
                if (_lock(this->signalSender, signalSender, "SignalSender")) {
                    signalSender->sendSignal(Signal::MainMenu);
                }
            } else if (SDLK_LCTRL == keysym) {
                lCtrl = false;
            } else if (SDLK_RCTRL == keysym) {
                rCtrl = false;
            }
        } else if (SDL_KEYDOWN == event.type) {
            auto keysym = event.key.keysym.sym;
            
            if (SDLK_LCTRL == keysym) {
                lCtrl = true;
            } else if (SDLK_RCTRL == keysym) {
                rCtrl = true;
            }
        } else if (SDL_MOUSEBUTTONUP == event.type && event.button.button == SDL_BUTTON_LEFT) {
            clicked = true;
            mousePos.i = event.button.x;
            mousePos.j = event.button.y;
        } else if (SDL_MOUSEMOTION == event.type) {
            mouseMoved = true;
            mousePos.i = event.motion.x;
            mousePos.j = event.motion.y;
        }
    }
    
    void MapEditor::update() {
        
    }
    
    void MapEditor::postUpdate() {
        clicked = false;
        mouseMoved = false;
    }
    
    void MapEditor::handleSignal(Signal signal) {
        if (Signal::MapEditor == signal) {
            Drawable::enable();
            EventListener::enable();
            Updatable::enable();
        } else {
            Drawable::disable();
            EventListener::disable();
            Updatable::enable();
        }
    }
    
    void MapEditor::load(shared_ptr<SDL_Renderer> renderer) {
        Font font("PressStart2P.ttf", 45, renderer);
        
        noMap = font.write("No Map Loaded");
    }
    
    void MapEditor::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
        noMap.position().i = newSize.widthHalf() - noMap.rectangle().widthHalf();
        noMap.position().j = newSize.heightHalf() - noMap.rectangle().heightHalf();
    }
    
    void MapEditor::setLoopQuiter(weak_ptr<LoopQuiter> loopQuiter) {
        this->loopQuiter = loopQuiter;
    }
    
    void MapEditor::setSignalSender(weak_ptr<SignalSender> signalSender) {
        this->signalSender = signalSender;
    }
}
