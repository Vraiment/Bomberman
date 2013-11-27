//
//  Brick.cpp
//  Bomberman
//
//  Created on 11/14/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Brick.hpp"

namespace Bomberman {
	Brick::Brick(Coordinate position, bool destructible) : _position(position), _destructible(destructible) {
		
	}
	
	bool Brick::destructible() const {
		return _destructible;
	}
	
	Coordinate Brick::position() const {
		return _position;
	}
}
