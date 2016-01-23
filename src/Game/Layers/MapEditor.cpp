//
//  MapEditor.cpp
//  Bomberman
//
//  Created on 21/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#include "MapEditor.hpp"

#include <SDL2/SDL.h>
#include <string>

#include "../../Core/Font.hpp"
#include "../../Core/Log/LogSystem.h"
#include "../../Core/Texture.hpp"
#include "../../Core/SignalSender.hpp"
#include "../../Core/Utils/PointerUtils.hpp"

#include "../Signal.hpp"

using namespace std;

namespace Bomberman {
    const int fontSize = 20;
    
    const int leftMargin = 5;
    const int rightMargin = 15;
    const int verticalMargin = leftMargin + rightMargin;
    
    const int topMargin = 5;
    const int bottomMargin = 5;
    const int horizontalMargin = topMargin + bottomMargin;
    
    const Color menuBarColor = Color(0xA0);
    const Color menuBarSelectedColor = Color(0x70);
    
    class MapEditor::MenuBarItem {
    public:
        MenuBarItem(Texture texture, Texture bg) : texture(texture), bg(bg), showing(false) {
            
        }
        
        virtual ~MenuBarItem() {
            
        }
        
        void setPosition(Coordinate position) {
            bgRect.i = position.i;
            bgRect.j = position.j;
            bgRect.width = texture.rectangle().width + verticalMargin;
            bgRect.height = texture.rectangle().height + horizontalMargin;
            
            texture.position().i = position.i + leftMargin;
            texture.position().j = position.j + topMargin;
        }
        
        void draw() {
            if (showing) {
                bg.setColor(menuBarSelectedColor);
            } else {
                bg.setColor(menuBarColor);
            }
            
            bg.rectangle() = bgRect;
            bg.draw();
            
            texture.draw();
        }
        
        bool select(Coordinate position) {
            showing = bg.rectangle().contains(position);
            
            return showing;
        }
        
        int width() {
            return bgRect.width;
        }
        
    private:
        const Color clickedColor;
        
        bool showing;
        Rectangle bgRect;
        Texture texture, bg;
    };
    
    template <typename T>
    bool _lock(weak_ptr<T> in, shared_ptr<T>& out, string component) {
        bool result = lockWeakPointer(in, out);
        
        if (!result) {
            Log::get() << "No " << component << " for MapEditor" << LogLevel::error;
        }
        
        return result;
    }
    
    MapEditor::MapEditor() : clicked(false), menuClicked(false) {
        
    }
    
    MapEditor::~MapEditor() {
        
    }
    
    void MapEditor::draw() {
        background.setColor(menuBarColor);
        background.rectangle() = menuBarRect;
        background.draw();
        
        for (auto menuBarItem : menuBar) {
            menuBarItem->draw();
        }
    }
    
    void MapEditor::listenEvent(SDL_Event event) {
        shared_ptr<SignalSender> signalSender;
        if (SDL_KEYUP == event.type && _lock(this->signalSender, signalSender, "SignalSender")) {
            auto keysym = event.key.keysym.sym;
            
            if (SDLK_ESCAPE == keysym) {
                signalSender->sendSignal(Signal::MainMenu);
            }
        } else if (SDL_MOUSEBUTTONUP == event.type && event.button.button == SDL_BUTTON_LEFT) {
            clicked = true;
            mousePos.i = event.button.x;
            mousePos.j = event.button.y;
        } else if (SDL_MOUSEMOTION == event.type) {
            mousePos.i = event.motion.x;
            mousePos.j = event.motion.y;
        }
    }
    
    void MapEditor::update() {
        if (clicked) {
            for (auto menuBarEntry : menuBar) {
                menuClicked = menuBarEntry->select(mousePos);
                
                if (menuClicked) {
                    break;
                }
            }
            
            clicked = false;
        } else if (menuClicked) {
            for (auto menuBarEntry : menuBar) {
                menuBarEntry->select(mousePos);
            }
        }
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
        Font font("PressStart2P.ttf", fontSize, renderer);
        
        menuBarRect.height = font.maxHeight() + horizontalMargin;
        
        background = Texture::createRectangle(1, 1, Color::WHITE, renderer);
        
        Coordinate position = Coordinate::ZERO;
        for (auto title : { "File", "Elements", "Items", "Help" }) {
            auto menuBarItem = make_shared<MenuBarItem>(font.write(title), background);
            menuBarItem->setPosition(position);
            this->menuBar.push_back(menuBarItem);
            
            position.i += menuBarItem->width();
        }
    }
    
    void MapEditor::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
        menuBarRect.width = newSize.width;
    }
    
    void MapEditor::setSignalSender(weak_ptr<SignalSender> signalSender) {
        this->signalSender = signalSender;
    }
}
