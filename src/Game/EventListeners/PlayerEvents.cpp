//
//  PlayerEvents.cpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "PlayerEvents.hpp"

#include <SDL2/SDL.h>

#include "../Constants.hpp"
#include "../CommandFactory.hpp"
#include "../../Core/CommandQueue.hpp"
#include "../Elements/Player.hpp"
#include "../../Core/Drawable.hpp"
#include "../../Core/Updatable.hpp"
#include "../Map/TileMap.hpp"

using namespace std;
using namespace Bomberman::Constants;

namespace Bomberman {
    PlayerEvents::PlayerEvents(shared_ptr<CommandFactory> commandFactory, shared_ptr<CommandQueue> commandQueue, shared_ptr<Player> player) : commandFactory(commandFactory), commandQueue(commandQueue), player(player) {
        
    }
    
    PlayerEvents::~PlayerEvents() {
        
    }
    
    void PlayerEvents::setConsoleEventListener(shared_ptr<EventListener> consoleEventListener) {
        this->consoleEventListener = consoleEventListener;
    }
    
    void PlayerEvents::setMainMenuLayer(shared_ptr<Drawable> mainMenuDrawable, shared_ptr<Updatable> mainMenuUpdatable) {
        this->mainMenuDrawable = mainMenuDrawable;
        this->mainMenuUpdatable = mainMenuUpdatable;
    }
    
    void PlayerEvents::addInGameLayer(shared_ptr<Drawable> inGameDrawable, shared_ptr<Updatable> inGameUpdatable) {
        inGameDrawables.push_back(inGameDrawable);
        inGameUpdatables.push_back(inGameUpdatable);
    }
    
    void PlayerEvents::setTileMap(shared_ptr<TileMap> tileMap) {
        this->tileMap = tileMap;
    }
    
    void PlayerEvents::listenEvent(SDL_Event event) {
        shared_ptr<Command> command;
        
        if (player->isDead()) {
            if (player->getLifesCount() <= 0) {
                if (SDL_KEYUP == event.type && SDLK_RETURN == event.key.keysym.sym) {
                    while (!inGameDrawables.empty()) {
                        inGameDrawables.back()->finish();
                        inGameDrawables.pop_back();
                        
                        inGameUpdatables.back()->finish();
                        inGameUpdatables.pop_back();
                    }
                    
                    consoleEventListener->finish();
                    
                    mainMenuDrawable->enable();
                    mainMenuUpdatable->enable();
                    
                    finish();
                }
            }
            
            return;
        }
        
        if (tileMap->playerWins()) {
            disable();
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
}
