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
    const int menuTopSpacing = 2;
    
    class MapEditor::MenuItem {
    public:
        MenuItem(Texture texture, Texture bg) : visible (false), texture(texture), bg(bg) {
            
        }
        
        virtual ~MenuItem() {
            
        }
        
        void draw(Coordinate position) {
            texture.position() = position;
            bg.rectangle() = texture.rectangle();
            
            bg.draw();
            texture.draw();
        }
        
        bool visible;
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
    
    MapEditor::~MapEditor() {
        
    }
    
    void MapEditor::draw() {
        background.rectangle() = menubar;
        background.draw();
        
        Coordinate position =  Coordinate(0, menuTopSpacing);
        for (auto menuItem : menu) {
            menuItem->draw(position);
            position.i += menuItem->texture.rectangle().width;
        }
    }
    
    void MapEditor::listenEvent(SDL_Event event) {
        shared_ptr<SignalSender> signalSender;
        if (SDL_KEYUP == event.type && _lock(this->signalSender, signalSender, "SignalSender")) {
            signalSender->sendSignal(Signal::MainMenu);
        }
    }
    
    void MapEditor::update() {
        
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
        
        menubar.height = font.maxHeight() + menuTopSpacing;
        
        background = Texture::createRectangle(1, 1, Color(0xE0), renderer);
        
        for (auto title : { " File ", " Elements ", " Items ", " Help " }) {
            auto menuItem = make_shared<MenuItem>(font.write(title), background);
            this->menu.emplace_back(menuItem);
        }
    }
    
    void MapEditor::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
        menubar.width = newSize.width;
    }
    
    void MapEditor::setSignalSender(weak_ptr<SignalSender> signalSender) {
        this->signalSender = signalSender;
    }
}
