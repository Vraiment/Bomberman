//
//  PlayerEvents.hpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __PlayerEvents__hpp__
#define __PlayerEvents__hpp__

#include "../../Core/EventListener.hpp"

#include <memory>
#include <vector>

namespace Bomberman {
    class CommandFactory;
    class CommandQueue;
    
    class PlayerEvents : public EventListener {
    public:
        void listenEvent(SDL_Event event);
        
        void setCommandFactory(std::weak_ptr<CommandFactory> commandFactory);
        void setCommandQueue(std::weak_ptr<CommandQueue> commandQueue);
        
    private:
        std::weak_ptr<CommandFactory> commandFactory;
        std::weak_ptr<CommandQueue> commandQueue;
    };
}

#endif //__PlayerEvents__hpp__
