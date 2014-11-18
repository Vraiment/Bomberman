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
#include "../CommandQueue.hpp"

using namespace std;
using namespace Bomberman::Constants;

namespace Bomberman {
	PlayerEvents::PlayerEvents(shared_ptr<CommandFactory> commandFactory, shared_ptr<CommandQueue> commandQueue) : commandFactory(commandFactory), commandQueue(commandQueue) {
		
	}
	
	PlayerEvents::~PlayerEvents() {
		
	}
	
	void PlayerEvents::listenEvent(SDL_Event event) {
		shared_ptr<Command> command;
		
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
					
				default:
					break;
			}
		}
		
		if (command) {
			commandQueue->addCommand(command);
		}
	}
}
