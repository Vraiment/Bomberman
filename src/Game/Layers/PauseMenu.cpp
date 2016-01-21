//
//  PauseMenu.cpp
//  Bomberman
//
//  Created on 13/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#include "PauseMenu.hpp"

#include "../../Core/Font.hpp"
#include "../../Core/Log/LogSystem.h"
#include "../../Core/LoopQuiter.hpp"
#include "../../Core/Utils/PointerUtils.hpp"
#include "../../Core/SignalSender.hpp"

#include "../Signal.hpp"

#include <SDL2/SDL.h>

using namespace std;

namespace Bomberman {
    template <typename T>
    bool _lock(weak_ptr<T> in, shared_ptr<T>& out, string component) {
        bool result = lockWeakPointer(in, out);
        
        if (!result) {
            Log::get() << "No " << component << " for PauseMenu" << LogLevel::error;
        }
        
        return result;
    }
    
    PauseMenu::PauseMenu() : selected(-1), clicking(false) {
        
    }
    
    void PauseMenu::listenEvent(SDL_Event event) {
        Coordinate position;
        
        if (Drawable::isEnabled() && Updatable::isEnabled()) {
            if (SDL_MOUSEBUTTONDOWN == event.type) {
                SDL_GetMouseState(&position.i, &position.j);
                
                clicking = true;
                select(position);
            } else if (SDL_MOUSEBUTTONUP == event.type) {
                clicking = false;
                pushSelectedButton();
            } else if (SDL_MOUSEMOTION == event.type) {
                SDL_GetMouseState(&position.i, &position.j);
                
                select(position);
            } else if (SDL_KEYUP == event.type) {
                auto keySym = event.key.keysym.sym;
                
                if (SDLK_UP == keySym && selected > 0 && !clicking) {
                    --selected;
                } else if (SDLK_DOWN == keySym && selected < 2 && !clicking) {
                    ++selected;
                } else if (SDLK_RETURN == keySym && selected >= 0 && selected < 3 && !clicking) {
                    pushSelectedButton();
                } else if (SDLK_ESCAPE == keySym) {
                    shared_ptr<SignalSender> signalSender;
                    if (_lock(this->signalSender, signalSender, "SignalSender")) {
                        signalSender->sendSignal(Signal::InGame);
                    }
                }
            }
        } else if (SDL_KEYUP == event.type && SDLK_ESCAPE == event.key.keysym.sym) {
            shared_ptr<SignalSender> signalSender;
            if (_lock(this->signalSender, signalSender, "SignalSender")) {
                signalSender->sendSignal(Signal::PauseGame);
            }
        }
    }
    
    void PauseMenu::draw() {
        background.draw();
        
        continueGame.draw();
        quitToMainMenu.draw();
        quitToDesktop.draw();
    }
    
    void PauseMenu::update() {
        if (0 == selected) {
            continueGame.setColor(Color::CYAN);
            quitToMainMenu.setColor(Color::WHITE);
            quitToDesktop.setColor(Color::WHITE);
        } else if (1 == selected) {
            continueGame.setColor(Color::WHITE);
            quitToMainMenu.setColor(Color::CYAN);
            quitToDesktop.setColor(Color::WHITE);
        } else if (2 == selected) {
            continueGame.setColor(Color::WHITE);
            quitToMainMenu.setColor(Color::WHITE);
            quitToDesktop.setColor(Color::RED);
        } else {
            continueGame.setColor(Color::WHITE);
            quitToMainMenu.setColor(Color::WHITE);
            quitToDesktop.setColor(Color::WHITE);
        }
    }
    
    void PauseMenu::handleSignal(Signal signal) {
        if (Signal::InGame == signal || Signal::HideConsole == signal) {
            EventListener::enable();
            Drawable::disable();
            Updatable::disable();
        } else if (signalIn(signal, { Signal::PauseGame, Signal::PlayerDead, Signal::PlayerAlive })) {
            EventListener::enable();
            Drawable::enable();
            Updatable::enable();
        } else {
            EventListener::disable();
            Drawable::disable();
            Updatable::disable();
        }
    }
    
    void PauseMenu::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
        int interline = 25;
        int totalHeight = (interline * 2) + continueGame.rectangle().height + quitToMainMenu.rectangle().height + quitToDesktop.rectangle().height;
        
        continueGame.position().i = newSize.widthHalf() - continueGame.rectangle().widthHalf();
        continueGame.position().j = (newSize.height - totalHeight) / 2;
        
        quitToMainMenu.position().i = newSize.widthHalf() - quitToMainMenu.rectangle().widthHalf();
        quitToMainMenu.position().j = continueGame.rectangle().bottom() + interline;
        
        quitToDesktop.position().i = newSize.widthHalf() - quitToDesktop.rectangle().widthHalf();
        quitToDesktop.position().j = quitToMainMenu.rectangle().bottom() + interline;
        
        background.rectangle() = newSize;
    }
    
    void PauseMenu::load(shared_ptr<SDL_Renderer> renderer) {
        background = Texture::createRectangle(1, 1, Color::BLACK, renderer);
        background.setAlpha(static_cast<uint8_t>(Texture::OPAQUE * .5));
        
        Font font("PressStart2P.ttf", 35, renderer);
        
        continueGame = font.write("Continue game");
        quitToMainMenu = font.write("Quit map");
        quitToDesktop = font.write("Quit to desktop");
    }
    
    void PauseMenu::pushSelectedButton() {
        shared_ptr<SignalSender> signalSender;
        shared_ptr<LoopQuiter> loopQuiter;
        
        if (selected < 0 ||
            !_lock(this->signalSender, signalSender, "SignalSender") ||
            !_lock(this->loopQuiter, loopQuiter, "LoopQuiter")) {
            return;
        }
        
        if (0 == selected) {
            signalSender->sendSignal(Signal::InGame);
        } else if (1 == selected) {
            signalSender->sendSignal(Signal::MainMenu);
        } else if (2 == selected) {
            loopQuiter->quitLoop();
        }
    }
    
    void PauseMenu::select(Coordinate position) {
        if (continueGame.rectangle().contains(position)) {
            selected = 0;
        } else if (quitToMainMenu.rectangle().contains(position)) {
            selected = 1;
        } else if (quitToDesktop.rectangle().contains(position)) {
            selected = 2;
        } else {
            selected = -1;
        }
    }
    
    void PauseMenu::setSignalSender(weak_ptr<SignalSender> signalSender) {
        this->signalSender = signalSender;
    }
    
    void PauseMenu::setLoopQuiter(weak_ptr<LoopQuiter> loopQuiter) {
        this->loopQuiter = loopQuiter;
    }
    
    void PauseMenu::show() {
        Drawable::enable();
        Updatable::enable();
    }
    
    void PauseMenu::hide() {
        Drawable::disable();
        Updatable::disable();
        
        clicking = false;
        selected = -1;
    }
}
