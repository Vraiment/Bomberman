//
//  LevelListLayer.cpp
//  Bomberman
//
//  Created on 12/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#include "LevelListLayer.hpp"

#include "../../Core/Math/Rectangle.hpp"
#include "../../Core/Texture.hpp"
#include "../../Core/Utils/OperatingSystem.hpp"
#include "../../Core/Log/LogSystem.h"

#include "../Director.hpp"

#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>

using namespace std;

namespace Bomberman {
    enum class LevelListLayer::Button {
        none,
        reload,
        cancel,
        ok
    };
    
    bool isMapFile(string path) {
        ifstream mapFile(path);
        
        if (mapFile.good()) {
            string line;
            getline(mapFile, line);
            
            return line == "#<mapfile>";
        }
        
        return false;
    }
    
    LevelListLayer::LevelListLayer() : selected(0), newSelected(-1), selectedButton(Button::none), clickedButton(Button::none) {
        
    }
    
    void LevelListLayer::listenEvent(SDL_Event event) {
        Coordinate position;
        
        if (SDL_MOUSEBUTTONDOWN == event.type) {
            SDL_GetMouseState(&position.i, &position.j);
            
            click(position);
        } else if (SDL_MOUSEMOTION == event.type) {
            SDL_GetMouseState(&position.i, &position.j);
            
            select(position);
        } else if (SDL_KEYUP == event.type) {
            auto keySym = event.key.keysym.sym;
            
            if (SDLK_UP == keySym) {
                newSelected = selected - 1;
            } else if (SDLK_DOWN == keySym) {
                newSelected = selected + 1;
            }
        }
    }
    
    void LevelListLayer::draw() {
        background.draw();
        
        Coordinate position = background.rectangle();
        position.i += 10;
        position.j += 10;
        for (auto&& map : maps) {
            map.second.rectangle() = position;
            map.second.draw();
            
            position.j += map.second.rectangle().height + 5;
        }
        
        cancel.draw();
        reload.draw();
        ok.draw();
    }
    
    void LevelListLayer::update() {
        // Set mouseover effects
        if (Button::cancel == selectedButton) {
            reload.setColor(Color::WHITE);
            cancel.setColor(Color::RED);
            ok.setColor(Color::WHITE);
        } else if (Button::reload == selectedButton) {
            reload.setColor(Color::YELLOW);
            cancel.setColor(Color::WHITE);
            ok.setColor(Color::WHITE);
        } else if (Button::ok == selectedButton){
            reload.setColor(Color::WHITE);
            cancel.setColor(Color::WHITE);
            ok.setColor(Color::GREEN);
        } else {
            reload.setColor(Color::WHITE);
            cancel.setColor(Color::WHITE);
            ok.setColor(Color::WHITE);
        }
        
        if (newSelected >= 0 && newSelected < maps.size()) {
            maps[selected].second.setColor(Color::WHITE);
            selected = newSelected;
            maps[selected].second.setColor(Color::BLUE);
        }
        
        // Click stuff
        if (Button::cancel == clickedButton) {
            if (!director.expired()) {
                auto director = this->director.lock();
                director->hideLevelList();
            } else {
                Log::get() << "No Director set for LevelListLayer" << LogLevel::error;
            }
            
            clickedButton = Button::none;
        } else if (Button::reload == clickedButton) {
            fillMapList();
            clickedButton = Button::none;
        } else if (Button::ok == clickedButton){
            if (!director.expired()) {
                auto director = this->director.lock();
                director->loadLevel(maps[selected].first);
            } else {
                Log::get() << "No Director set for LevelListLayer" << LogLevel::error;
            }
            
            clickedButton = Button::none;
        }
    }
    
    void LevelListLayer::load(shared_ptr<SDL_Renderer> renderer) {
        font = Font("PressStart2P.ttf", 15, renderer);
        
        Font buttons = Font("PressStart2P.ttf", 25, renderer);
        
        reload = buttons.write("Reload");
        cancel = buttons.write("Cancel");
        ok = buttons.write("Play");
        
        background = Texture::createRectangle(1, 1, Color(0x77), renderer);
    }
    
    void LevelListLayer::fillMapList() {
        vector<string> files;
        
        maps.clear();
        
        if (!listDir("maps", files)) {
            Log::get() << "Could not list \"maps\" directory" << LogLevel::error;
            return;
        }
        
        for (auto fileName : files) {
            if (!isMapFile(getPath({ "maps" }, fileName))) {
                continue;
            }
            
            // Remove extension from file
            size_t posOfExtension = fileName.find_last_of(".");
            string baseName = (string::npos != posOfExtension) ? fileName.substr(0, posOfExtension) : fileName;
            
            // Create the texture
            Texture texture = font.write(baseName);
            maps.emplace_back(fileName, texture);
        }
        
        if (!maps.empty()) {
            newSelected = 0;
        } else {
            newSelected = -1;
        }
    }
    
    void LevelListLayer::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
        background.rectangle().i = newSize.width * .05;
        background.rectangle().width = newSize.width * .9;
        
        background.rectangle().j = newSize.height * .05;
        background.rectangle().height = (newSize.height * .95) - ok.rectangle().height - 50;
        
        cancel.rectangle().i = background.rectangle().i;
        cancel.rectangle().j = background.rectangle().bottom() + 20;
        
        reload.rectangle().i = background.rectangle().widthCenter() - reload.rectangle().widthHalf();
        reload.rectangle().j = cancel.rectangle().j;
        
        ok.rectangle().i = background.rectangle().right() - ok.rectangle().width;
        ok.rectangle().j = reload.rectangle().j;
    }
    
    void LevelListLayer::setDirector(weak_ptr<Director> director) {
        this->director = director;
    }
    
    void LevelListLayer::click(Coordinate position) {
        if (cancel.rectangle().contains(position)) {
            clickedButton = Button::cancel;
        } else if (reload.rectangle().contains(position)) {
            clickedButton = Button::reload;
        } else if (ok.rectangle().contains(position)) {
            clickedButton = Button::ok;
        } else {
            clickedButton = Button::none;
        }
    }
    
    void LevelListLayer::select(Coordinate position) {
        if (cancel.rectangle().contains(position)) {
            selectedButton = Button::cancel;
        } else if (reload.rectangle().contains(position)) {
            selectedButton = Button::reload;
        } else if (ok.rectangle().contains(position)) {
            selectedButton = Button::ok;
        } else {
            selectedButton = Button::none;
            
            for (int n = 0; n < maps.size(); ++n) {
                if (maps[n].second.rectangle().contains(position)) {
                    newSelected = n;
                    break;
                }
            }
        }
    }
}
