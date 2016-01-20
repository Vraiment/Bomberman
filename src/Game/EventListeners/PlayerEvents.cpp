//
//  PlayerEvents.cpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "PlayerEvents.hpp"

#include <SDL2/SDL.h>

#include "../../Core/CommandQueue.hpp"
#include "../../Core/Log/LogSystem.h"
#include "../../Core/Utils/PointerUtils.hpp"

#include "../Constants.hpp"
#include "../CommandFactory.hpp"
#include "../Elements/Player.hpp"
#include "../Map/TileMap.hpp"
#include "../Signal.hpp"

using namespace std;
using namespace Bomberman::Constants;

namespace Bomberman {
    template <typename T>
    bool _lock(weak_ptr<T> in, shared_ptr<T>& out, string component) {
        bool result = lockWeakPointer(in, out);
        
        if (!result) {
            Log::get() << "No " << component << " for PlayerEvents" << LogLevel::error;
        }
        
        return result;
    }
    
    void PlayerEvents::listenEvent(SDL_Event event) {
        shared_ptr<Command> command;
        shared_ptr<CommandFactory> commandFactory;
        shared_ptr<CommandQueue> commandQueue;
        
        if (!_lock(this->commandFactory, commandFactory, "CommandFactory") ||
            !_lock(this->commandQueue, commandQueue, "CommandQueue")) {
            return;
        }
        
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    command = commandFactory->sendMessage(OBJ_PLAYER, MSG_MOVE, { ARG_RIGHT });
                    break;
                    
                case SDLK_UP:
                    command = commandFactory->sendMessage(OBJ_PLAYER, MSG_MOVE, { ARG_UP });
                    break;
                    
                case SDLK_LEFT:
                    command = commandFactory->sendMessage(OBJ_PLAYER, MSG_MOVE, { ARG_LEFT });
                    break;
                    
                case SDLK_DOWN:
                    command = commandFactory->sendMessage(OBJ_PLAYER, MSG_MOVE, { ARG_DOWN });
                    break;
                    
                default:
                    break;
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_b:
                    command = commandFactory->sendMessage(OBJ_PLAYER, MSG_SETBOMB);
                    break;
                    
                case SDLK_e:
                    command = commandFactory->sendMessage(OBJ_PLAYER, MSG_IGNITE);
                    break;
                    
                default:
                    break;
            }
        }
        
        if (command) {
            commandQueue->addCommand(command);
        }
    }
    
    void PlayerEvents::handleSignal(Signal signal) {
        if (Signal::InGame == signal) {
            EventListener::enable();
        } else {
            EventListener::disable();
        }
    }
    
    void PlayerEvents::setCommandFactory(weak_ptr<CommandFactory> commandFactory) {
        this->commandFactory = commandFactory;
    }
    
    void PlayerEvents::setCommandQueue(weak_ptr<CommandQueue> commandQueue) {
        this->commandQueue = commandQueue;
    }
}
