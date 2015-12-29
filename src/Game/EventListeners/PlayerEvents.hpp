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
    class Layer;
    class Player;
    
    class PlayerEvents : public EventListener {
    public:
        PlayerEvents(std::shared_ptr<CommandFactory> commandFactory, std::shared_ptr<CommandQueue> commandQueue, std::shared_ptr<Player> player);
        ~PlayerEvents();
        
        void listenEvent(SDL_Event event);
        
        void setConsoleEventListener(std::shared_ptr<EventListener> consoleEventListener);
        void setMainMenuLayer(std::shared_ptr<Layer> mainMenuLayer);
        void addInGameLayer(std::shared_ptr<Layer> inGameLayer);
        
    private:
        std::shared_ptr<Player> player;
        std::shared_ptr<CommandFactory> commandFactory;
        std::shared_ptr<CommandQueue> commandQueue;
        std::shared_ptr<Layer> mainMenuLayer;
        std::shared_ptr<EventListener> consoleEventListener;
        std::vector<std::shared_ptr<Layer>> inGameLayers;
    };
}

#endif //__PlayerEvents__hpp__
