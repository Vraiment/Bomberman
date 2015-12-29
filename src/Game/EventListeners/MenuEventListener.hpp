//
//  MenuEventListener.hpp
//  Bomberman
//
//  Created by Jorge Esteban Macías Calleja on 27/12/15.
//  Copyright © 2015 Vraiment. All rights reserved.
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
