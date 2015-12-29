//
//  MenuEventListener.hpp
//  Bomberman
//
//  Created on 27/12/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __MenuEventListener__hpp__
#define __MenuEventListener__hpp__

#include "../../Core/EventListener.hpp"

#include <memory>

namespace Bomberman {
    class MainMenuLayer;
    
    class MenuEventListener : public EventListener {
    public:
        MenuEventListener(std::shared_ptr<MainMenuLayer> menu);
        
        void listenEvent(SDL_Event event);
        
    private:
        std::shared_ptr<MainMenuLayer> menu;
    };
}

#endif //__MenuEventListener__hpp__
