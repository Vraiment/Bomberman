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

#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>

using namespace std;

namespace Bomberman {
    enum class SelectedButton {
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
    
    LevelListLayer::LevelListLayer() : selected(0), newSelected(-1), selectedButton(SelectedButton::none) {
        
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
                newSelected = selected - 1;;
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
            map.rectangle() = position;
            map.draw();
            
            position.j += map.rectangle().height + 5;
        }
        
        cancel.draw();
        reload.draw();
        ok.draw();
    }
    
    void LevelListLayer::update() {
        if (SelectedButton::cancel == selectedButton) {
            reload.setColor(Color::WHITE);
            cancel.setColor(Color::RED);
            ok.setColor(Color::WHITE);
        } else if (SelectedButton::reload == selectedButton) {
            reload.setColor(Color::YELLOW);
            cancel.setColor(Color::WHITE);
            ok.setColor(Color::WHITE);
        } else if (SelectedButton::ok == selectedButton){
            reload.setColor(Color::WHITE);
            cancel.setColor(Color::WHITE);
            ok.setColor(Color::GREEN);
        } else {
            reload.setColor(Color::WHITE);
            cancel.setColor(Color::WHITE);
            ok.setColor(Color::WHITE);
        }
        
        if (newSelected >= 0 && newSelected < maps.size()) {
            maps[selected].setColor(Color::WHITE);
            selected = newSelected;
            maps[selected].setColor(Color::BLUE);
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
            maps.push_back(texture);
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
    
    void LevelListLayer::click(Coordinate position) {
        
    }
    
    void LevelListLayer::select(Coordinate position) {
        if (cancel.rectangle().contains(position)) {
            selectedButton = SelectedButton::cancel;
        } else if (reload.rectangle().contains(position)) {
            selectedButton = SelectedButton::reload;
        } else if (ok.rectangle().contains(position)) {
            selectedButton = SelectedButton::ok;
        } else {
            selectedButton = SelectedButton::none;
            
            for (int n = 0; n < maps.size(); ++n) {
                if (maps[n].rectangle().contains(position)) {
                    newSelected = n;
                    break;
                }
            }
        }
    }
}
