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

namespace Bomberman {
    class CommandFactory;
    class CommandQueue;
    class Player;
    
    class PlayerEvents : public EventListener {
    public:
        PlayerEvents(std::shared_ptr<CommandFactory> commandFactory, std::shared_ptr<CommandQueue> commandQueue, std::shared_ptr<Player> player);
        ~PlayerEvents();
        
        void listenEvent(SDL_Event event);
        
    private:
        std::shared_ptr<Player> player;
        std::shared_ptr<CommandFactory> commandFactory;
        std::shared_ptr<CommandQueue> commandQueue;
    };
}

#endif //__PlayerEvents__hpp__
