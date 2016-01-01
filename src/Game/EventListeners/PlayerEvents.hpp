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
    class Drawable;
    class Updatable;
    class CommandFactory;
    class CommandQueue;
    class Player;
    
    class PlayerEvents : public EventListener {
    public:
        PlayerEvents(std::shared_ptr<CommandFactory> commandFactory, std::shared_ptr<CommandQueue> commandQueue, std::shared_ptr<Player> player);
        ~PlayerEvents();
        
        void listenEvent(SDL_Event event);
        
        void setConsoleEventListener(std::shared_ptr<EventListener> consoleEventListener);
        void setMainMenuLayer(std::shared_ptr<Drawable> mainMenuDrawable, std::shared_ptr<Updatable> mainMenuUpdatable);
        void addInGameLayer(std::shared_ptr<Drawable> inGameDrawable, std::shared_ptr<Updatable> updatable);
        
    private:
        std::shared_ptr<Player> player;
        std::shared_ptr<CommandFactory> commandFactory;
        std::shared_ptr<CommandQueue> commandQueue;
        std::shared_ptr<Drawable> mainMenuDrawable;
        std::shared_ptr<Updatable> mainMenuUpdatable;
        std::shared_ptr<EventListener> consoleEventListener;
        std::vector<std::shared_ptr<Drawable>> inGameDrawables;
        std::vector<std::shared_ptr<Updatable>> inGameUpdatables;
    };
}

#endif //__PlayerEvents__hpp__
