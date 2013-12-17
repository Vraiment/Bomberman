//
//  PlayerEvents.cpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "PlayerEvents.hpp"

#include <SDL2/SDL.h>

#include "../CommandFactory.hpp"
#include "../CommandQueue.hpp"

using namespace std;

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
					command = commandFactory->sendMessage("player", "move", { "right" });
					break;
					
				case SDLK_UP:
					command = commandFactory->sendMessage("player", "move", { "up" });
					break;
					
				case SDLK_LEFT:
					command = commandFactory->sendMessage("player", "move", { "left" });
					break;
					
				case SDLK_DOWN:
					command = commandFactory->sendMessage("player", "move", { "down" });
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
