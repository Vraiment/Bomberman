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
            for (auto item : items) {
                item.draw();
            }
        } else if (Page::HUD == page) {
            for (auto h : hud) {
                h.draw();
            }
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
                textRight = &itemsText;
            } else if (Page::Items == page) {
                textLeft = &instructionsText;
                textRight = &hudText;
            } else if (Page::HUD == page) {
                textLeft = &itemsText;
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
        itemsText = font.write("Items");
        hudText = font.write("User interface");
        
        loadInstructions(font, renderer);
        loadItems(font, renderer);
        loadHud(font, renderer);
    }
    
    void HowToPlay::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
        setInstructionsPos(newSize);
        
        prev.position().i = 20;
        prev.position().j = newSize.bottom() - prev.rectangle().height - 20;
        
        next.position().i = newSize.right() - next.rectangle().height - 20;
        next.position().j = newSize.bottom() - next.rectangle().height - 20;
        
        setInstructionsPos(newSize);
        setItemsPos(newSize);
        setHudPos(newSize);
    }
    
    void HowToPlay::setDirector(weak_ptr<Director> director) {
        this->director = director;
    }
    
    void HowToPlay::loadInstructions(Font font, shared_ptr<SDL_Renderer> renderer) {
        instructions.push_back(font.write("Move with the arrow keys"));
        instructions.emplace_back("arrows_tutorial.png", renderer);
        
        instructions.push_back(font.write("Press 'B' to place bombs"));
        instructions.emplace_back("bomb_tutorial.png", renderer);
        
        instructions.push_back(font.write("Destroy all the enemies"));
        instructions.emplace_back("enemies_tutorial.png", renderer);
        
        instructions.push_back(font.write("Destroy the brick walls, and find the door"));
        instructions.emplace_back("endgame_tutorial.png", renderer);
    }
    
    void HowToPlay::loadItems(Font font, shared_ptr<SDL_Renderer> renderer) {
        items.push_back(font.write("Increases the amount of bombs you can place"));
        items.emplace_back("extraBomb_tutorial.png", renderer);
        
        items.push_back(font.write("Increases the range of explosions"));
        items.emplace_back("increaseRange_tutorial.png", renderer);
        
        items.push_back(font.write("Controller: Bombs will explode with the 'E' key"));
        items.emplace_back("remote_tutorial.png", renderer);
    }
    
    void HowToPlay::loadHud(Font font, shared_ptr<SDL_Renderer> renderer) {
        hud.push_back(font.write("User interface"));
        hud.emplace_back("hud_tutorial.png", renderer);
        
        hud.push_back(Texture::createRectangle(1, 1, Color::WHITE, renderer));
        hud.push_back(font.write("Amount of lifes"));
        
        hud.push_back(Texture::createRectangle(1, 1, Color::WHITE, renderer));
        hud.push_back(font.write("Bombs controller"));
        
        hud.push_back(Texture::createRectangle(1, 1, Color::WHITE, renderer));
        hud.push_back(font.write("Amount of bombs"));
        
        hud.push_back(Texture::createRectangle(1, 1, Color::WHITE, renderer));
        hud.push_back(font.write("Explosion range"));
    }
    
    void HowToPlay::setInstructionsPos(Rectangle screenSize) {
        if (instructions.empty()) {
            return;
        }
        
        int spacing = 25;
        auto instruction = instructions.begin();
        
        instruction->position().i = screenSize.widthHalf() - instruction->rectangle().widthHalf();
        instruction->position().j = 25;
        
        for (auto prevInstructions = instructions.begin(); ++instruction != instructions.end(); ++prevInstructions) {
            instruction->position().i = screenSize.widthHalf() - instruction->rectangle().widthHalf();
            instruction->position().j = prevInstructions->rectangle().bottom() + spacing;
        }
    }
    
    void HowToPlay::setItemsPos(Rectangle screenSize) {
        if (items.empty()) {
            return;
        }
        
        int totalHeight = 0;
        for (auto item : items) {
            totalHeight += item.rectangle().height;
        }
        
        int spacing = 25;
        totalHeight += spacing * static_cast<int>(items.size() - 1);

        auto item = items.begin();
        
        item->position().i = screenSize.widthHalf() - item->rectangle().widthHalf();
        item->position().j = screenSize.heightHalf() - (totalHeight / 2);
        
        for (auto prevItem = items.begin(); ++item != items.end(); ++prevItem) {
            item->position().i = screenSize.widthHalf() - item->rectangle().widthHalf();
            item->position().j = prevItem->rectangle().bottom() + spacing;
        }
    }
    
    void HowToPlay::setHudPos(Rectangle screenSize) {
        const int spacing = 5;
        
        // Sample image
        auto& hudImage = hud[1];
        hudImage.position().i = screenSize.widthHalf() - hudImage.rectangle().widthHalf();
        hudImage.position().j = screenSize.heightHalf() - hudImage.rectangle().heightHalf();
        
        // Title
        auto& title = hud[0];
        title.position().i = screenSize.widthHalf() - title.rectangle().widthHalf();
        title.position().j = hudImage.rectangle().top() / 2;
        
        auto placeAbove = [hudImage] (int height, float percentage, Rectangle& text, Rectangle& line) {
            text.i = hudImage.position().i + (percentage * hudImage.rectangle().width) - text.widthHalf();
            text.j = hudImage.rectangle().top() - height - (2 * spacing) - text.height;
            
            line.width = 4;
            line.height = height;
            line.i = text.widthCenter() - line.widthHalf();
            line.j = text.bottom() + spacing;
        };
        
        auto placeBelow = [hudImage] (int height, float percentage, Rectangle& text, Rectangle& line) {
            text.i = hudImage.position().i + (percentage * hudImage.rectangle().width) - text.widthHalf();
            text.j = hudImage.rectangle().bottom() + height + (2 * spacing);
            
            line.width = 4;
            line.height = height;
            line.i = text.widthCenter() - line.widthHalf();
            line.j = hudImage.rectangle().bottom() + spacing;
        };
        
        // Place the lifes text
        placeAbove(25, .075, hud[3].rectangle(), hud[2].rectangle());
        
        // Place the controller text
        placeBelow(60, .22, hud[5].rectangle(), hud[4].rectangle());
        
        // Place the bombs amount text
        placeAbove(60, .37, hud[7].rectangle(), hud[6].rectangle());
        
        // Place the explosion range text
        placeBelow(25, .52, hud[9].rectangle(), hud[8].rectangle());
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
