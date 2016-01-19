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
    const Color normalColor = Color::WHITE;
    const Color selectedColor = Color::CYAN;
    
    template <typename T>
    bool _lock(weak_ptr<T>in, shared_ptr<T>& out, string component) {
        bool result = lockWeakPointer(in, out);
        
        if (!result) {
            Log::get() << "No " << component << " for HowToPlay" << LogLevel::error;
        }
        
        return result;
    }
    
    enum class HowToPlay::Page {
        None,
        Instructions,
        Items,
        HUD
    };
    
    HowToPlay::HowToPlay() : page(Page::None), nextPage(Page::None), hide(false) {
        
    }
    
    void HowToPlay::listenEvent(SDL_Event event) {
        if (SDL_KEYUP == event.type) {
            auto keysym = event.key.keysym.sym;
            
            if (SDLK_ESCAPE == keysym) {
                hide = true;
                nextPage = Page::Instructions;
            }
        } else if (SDL_MOUSEMOTION == event.type) {
            Coordinate position;
            SDL_GetMouseState(&position.i, &position.j);
            
            select(position);
        } else if (SDL_MOUSEBUTTONUP == event.type) {
            Coordinate position;
            SDL_GetMouseState(&position.i, &position.j);
            
            click(position);
        }
    }
    
    void HowToPlay::draw() {
        if (Page::Instructions == page) {
            for (auto instruction : instructions) {
                instruction.draw();
            }
        } else if (Page::Items == page) {
            
        } else if (Page::HUD == page) {
            
        }
        
        textLeft->draw();
        prev.draw();
        
        if (nullptr != textRight) {
            textRight->draw();
            next.draw();
        }
    }
    
    void HowToPlay::update() {
        if (Page::None != nextPage) {
            page = nextPage;
            nextPage = Page::None;
            
            if (Page::Instructions == page) {
                textLeft = &mainMenu;
                textRight = &items;
            } else if (Page::Items == page) {
                textLeft = &instructionsText;
                textRight = &hud;
            } else if (Page::HUD == page) {
                textLeft = &items;
                textRight = nullptr;
            }
            
            textLeft->position().i = prev.rectangle().i;
            textLeft->position().j = prev.rectangle().j - textLeft->rectangle().height;
            
            if (nullptr != textRight) {
                textRight->position().i = next.rectangle().right() - textRight->rectangle().width;
                textRight->position().j = next.rectangle().j - textRight->rectangle().height;
            }
        }
        
        if (hide) {
            shared_ptr<Director> director;
            if (_lock(this->director, director, "Director")) {
                director->hideHowToPlay();
            }
            
            hide = false;
        }
    }
    
    void HowToPlay::load(shared_ptr<SDL_Renderer> renderer) {
        nextPage = Page::Instructions;
        textLeft = textRight = &mainMenu;
        
        Font font("PressStart2P.ttf", 15, renderer);
        
        prev = Texture("arrow_left.png", renderer);
        prev.setColor(normalColor);
        next = Texture("arrow_right.png", renderer);
        next.setColor(normalColor);
        
        mainMenu = font.write("Main menu");
        instructionsText = font.write("Instructions");
        items = font.write("Items");
        hud = font.write("HUD");
        
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
    
    void HowToPlay::click(Coordinate position) {
        if (isRightButton(position)) {
            if (Page::Instructions == page) {
                nextPage = Page::Items;
            } else if (Page::Items == page) {
                nextPage = Page::HUD;
            }
        } else if (isLeftButton(position)) {
            if (Page::HUD == page) {
                nextPage = Page::Items;
            } else if (Page::Items == page) {
                nextPage = Page::Instructions;
            } else if (Page::Instructions == page) {
                hide = true;
            }
        }
    }
    
    void HowToPlay::select(Coordinate position) {
        if (isLeftButton(position)) {
            prev.setColor(selectedColor);
            next.setColor(normalColor);
        } else if (isRightButton(position)) {
            prev.setColor(normalColor);
            next.setColor(selectedColor);
        } else {
            prev.setColor(normalColor);
            next.setColor(normalColor);
        }
    }
    
    bool HowToPlay::isLeftButton(Coordinate position) {
        return prev.rectangle().contains(position) || textLeft->rectangle().contains(position);
    }
    
    bool HowToPlay::isRightButton(Coordinate position) {
        return next.rectangle().contains(position) || (nullptr != textRight && textRight->rectangle().contains(position));
    }
}
