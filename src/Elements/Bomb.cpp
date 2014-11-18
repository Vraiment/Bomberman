//
//  Bomb.cpp
//  Bomberman
//
//  Created on 17/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#include "Bomb.hpp"

#include <SDL2/SDL.h>

namespace Bomberman {
	const int Bomb::TTL = 300000;
	
	Bomb::Bomb(Coordinate position) : _position(position), _ttl(TTL), _exploded(false), _counting(false), _startTime(0) {
		
	}
	
	Coordinate Bomb::getPosition() const {
		return _position;
	}
	
	void Bomb::update() {
		if (_exploded) {
			return;
		}
		
		if (!_counting) {
			_counting = true;
			_startTime = SDL_GetTicks();
			
			return;
		}
		
		_ttl -= SDL_GetTicks() - _startTime;
		_exploded = _ttl <= 0;
	}
	
	bool Bomb::exploded() const {
		return _exploded;
	}
}
