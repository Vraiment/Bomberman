//
//  MenuEventListener.cpp
//  Bomberman
//
//  Created on 27/12/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "MenuEventListener.hpp"

#include <SDL2/SDL.h>

#include "../Layers/MainMenuLayer.hpp"
#include "../Log/LogSystem.h"
#include "../Math/Coordinate.hpp"

using namespace std;

namespace Bomberman {
    MenuEventListener::MenuEventListener(shared_ptr<MainMenuLayer> menu) : menu(menu) {
        
    }
    
    void MenuEventListener::listenEvent(SDL_Event event) {
        Coordinate position;
        
        if (menu->isZombie()) {
            _isZombie = true;
            return;
        }
        
        if (SDL_MOUSEBUTTONDOWN == event.type) {
            SDL_GetMouseState(&position.i, &position.j);
            
            menu->click(position);
        } else if (SDL_MOUSEMOTION == event.type) {
            SDL_GetMouseState(&position.i, &position.j);
            
            menu->select(position);
        }
    }
}
