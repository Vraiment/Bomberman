//
//  EventListener.hpp
//  Bomberman
//
//  Created on 05/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __EventListener__hpp__
#define __EventListener__hpp__

union SDL_Event;

#include "ScreenComponent.hpp"

namespace Bomberman {
    class EventListener : public ScreenComponent {
    public:
        virtual void listenEvent(SDL_Event event) = 0;
    };
}

#endif //__EventListener__hpp__
