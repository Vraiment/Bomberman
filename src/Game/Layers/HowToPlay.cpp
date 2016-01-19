//
//  HowToPlay.cpp
//  Bomberman
//
//  Created on 14/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#include "HowToPlay.hpp"

#include "../../Core/Font.hpp"
#include "../../Core/Log/LogSystem.h"
#include "../../Core/Utils/PointerUtils.hpp"

#include "../Director.hpp"

#include <SDL2/SDL.h>

using namespace std;

namespace Bomberman {
    const Color normalColor = Color::CYAN;
    const Color selectedColor = Color::BLUE;
    
    template <typename T>
    bool _lock(weak_ptr<T>in, shared_ptr<T>& out, string component) {
        bool result = lockWeakPointer(in, out);
        
        if (!result) {
            Log::get() << "No " << component << " for HowToPlay" << LogLevel::error;
        }
        
        return result;
    }
    
    enum class Page {
        Instructions,
        Items,
        HUD
    };
    
    void HowToPlay::listenEvent(SDL_Event event) {
        if (SDL_KEYUP == event.type) {
            auto keysym = event.key.keysym.sym;
            
            if (SDLK_ESCAPE == keysym) {
                shared_ptr<Director> director;
                if (_lock(this->director, director, "Director")) {
                    director->hideHowToPlay();
                }
            }
        } else if (SDL_MOUSEMOTION == event.type) {
            Coordinate position;
            SDL_GetMouseState(&position.i, &position.j);
            
            select(position);
        }
    }
    
    void HowToPlay::draw() {
        for (auto instruction : instructions) {
            instruction.draw();
        }
        
        prev.draw();
        next.draw();
    }
    
    void HowToPlay::update() {
        
    }
    
    void HowToPlay::load(shared_ptr<SDL_Renderer> renderer) {
        Font font("PressStart2P.ttf", 15, renderer);
        
        prev = Texture("arrow_left.png", renderer);
        prev.setColor(normalColor);
        next = Texture("arrow_right.png", renderer);
        next.setColor(normalColor);
        
        instructions.push_back(font.write("Move with the arrow keys"));
        instructions.emplace_back("arrows_tutorial.png", renderer);
        
        instructions.push_back(font.write("Press B to place bombs"));
        instructions.emplace_back("bomb_tutorial.png", renderer);
        
        instructions.push_back(font.write("Destroy all the enemies"));
        instructions.emplace_back("enemies_tutorial.png", renderer);
        
        instructions.push_back(font.write("Destroy the brick walls, and find the door"));
        instructions.emplace_back("endgame_tutorial.png", renderer);
    }
    
    void HowToPlay::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
        int spacing = 25;
        
        if (!instructions.empty()) {
            auto instruction = instructions.begin();
            
            instruction->position().i = newSize.widthHalf() - instruction->rectangle().widthHalf();
            instruction->position().j = 25;
            
            for (auto prevInstructions = instructions.begin(); ++instruction != instructions.end(); ++prevInstructions) {
                instruction->position().i = newSize.widthHalf() - instruction->rectangle().widthHalf();
                instruction->position().j = prevInstructions->rectangle().bottom() + spacing;
            }
        }
        
        prev.position().i = 20;
        prev.position().j = newSize.bottom() - prev.rectangle().height - 20;
        
        next.position().i = newSize.right() - next.rectangle().height - 20;
        next.position().j = newSize.bottom() - next.rectangle().height - 20;
    }
    
    void HowToPlay::setDirector(weak_ptr<Director> director) {
        this->director = director;
    }
    
    void HowToPlay::select(Coordinate position) {
        next.setColor(next.rectangle().contains(position) ? selectedColor : normalColor);
        prev.setColor(prev.rectangle().contains(position) ? selectedColor : normalColor);
    }
}
