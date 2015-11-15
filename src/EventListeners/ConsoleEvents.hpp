//
//  ConsoleEvents.hpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __ConsoleEvents__hpp__
#define __ConsoleEvents__hpp__

#include "../EventListener.hpp"

#include <memory>

namespace Bomberman {
    class CommandQueue;
    class Console;
    
    class ConsoleEvents : public EventListener {
    public:
        ConsoleEvents(std::shared_ptr<Console> console);
        ~ConsoleEvents();
        
        void listenEvent(SDL_Event event);
        
    private:
        std::shared_ptr<Console> console;
    };
}

#endif //__ConsoleEvents__hpp__
