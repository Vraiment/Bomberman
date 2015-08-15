//
//  ConsoleEvents.cpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "ConsoleEvents.hpp"
#include <SDL2/SDL.h>

#include "../CommandQueue.hpp"
#include "../Console.hpp"
#include "../Utils/Exception.hpp"

using namespace std;

namespace Bomberman {
	ConsoleEvents::ConsoleEvents(shared_ptr<Console> console) : console(console) {
		
	}
	
	ConsoleEvents::~ConsoleEvents() {
		
	}
	
	void ConsoleEvents::listenEvent(SDL_Event event) {
		if (console->visible()) {
			//capture keys
		} else {
			switchConsole(event);
		}
	}

	void ConsoleEvents::switchConsole(SDL_Event event) {
		if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
				case SDLK_BACKSPACE:
					console->show();
					break;
					
				case SDLK_ESCAPE:
					console->hide();
					break;
					
				default:
					break;
			}
		}
	}
}
