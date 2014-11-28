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
	const int Bomb::TTL = 3000;
	
	Bomb::Bomb(Coordinate position) : _position(position), _exploded(false) {
		
	}
	
	Coordinate Bomb::getPosition() const {
		return _position;
	}
	
	void Bomb::update() {
		if (_exploded) {
			return;
		}
		
		if (!timer.isCounting()) {
			timer.start();
		} else if (timer.getTime() >= TTL) {
			_exploded = true;
			timer.stop();
		}
	}
	
	void Bomb::forceExplosion() {
		_exploded = true;
	}
	
	bool Bomb::exploded() const {
		return _exploded;
	}
}
