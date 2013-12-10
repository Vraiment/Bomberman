//
//  PlayerEvents.cpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "PlayerEvents.hpp"

#include <SDL2/SDL.h>

#include "../TileMap.hpp"

using namespace std;

namespace Bomberman {
	PlayerEvents::PlayerEvents(shared_ptr<TileMap> tileMap) : tileMap(tileMap) {
		
	}
	
	PlayerEvents::~PlayerEvents() {
		
	}
	
	void PlayerEvents::listenEvent(SDL_Event event) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_RIGHT:
					tileMap->execute("player.move(right)");
					break;
					
				case SDLK_UP:
					tileMap->execute("player.move(up)");
					break;
					
				case SDLK_LEFT:
					tileMap->execute("player.move(left)");
					break;
					
				case SDLK_DOWN:
					tileMap->execute("player.move(down)");
					break;
					
				default:
					break;
			}
		}
	}
}
