//
//  ConsoleEvents.hpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __ConsoleEvents__hpp__
#define __ConsoleEvents__hpp__

#include "../../Core/EventListener.hpp"
#include "../../Core/SignalHandler.hpp"

#include <memory>

namespace Bomberman {
    class CommandQueue;
    class Console;
    
    class ConsoleEvents : public EventListener, public SignalHandler {
    public:
        void listenEvent(SDL_Event event);
        
        void setConsole(std::weak_ptr<Console> console);
        
        void handleSignal(Signal signal);
        
    private:
        std::weak_ptr<Console> console;
    };
}

#endif //__ConsoleEvents__hpp__
