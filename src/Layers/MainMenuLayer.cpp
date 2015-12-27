//
//  MainMenuLayer.cpp
//  Bomberman
//
//  Created on 27/16/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "MainMenuLayer.hpp"

#include "../Font.hpp"

#include "../Log/LogSystem.h"

using namespace std;

namespace Bomberman {
    const int MainMenuLayer::ENTRIES_SPACING = 100;
    
    MainMenuLayer::MainMenuLayer() : selected(nullptr) {
        
    }
    
    void MainMenuLayer::update() {
        
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
            
            startGame.setColor(Color::RED);
            selected =  &startGame;
        } else if (exit.rectangle().contains(position)) {
            if (selected && &exit != selected) {
                selected->setColor(Color::WHITE);
            }
            
            exit.setColor(Color::RED);
            selected = &exit;
        } else if (selected) {
            selected->setColor(Color::WHITE);
            selected = nullptr;
        }
    }
    
    void MainMenuLayer::click(Coordinate position) {
        if (startGame.rectangle().contains(position)) {
            Log::get() << "click in start" << LogLevel::info;
        } else if (exit.rectangle().contains(position)) {
            Log::get() << "click on exit" << LogLevel::info;
        }
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
