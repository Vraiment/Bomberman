//
//  Explosion.cpp
//  Bomberman
//
//  Created on 17/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#include "Explosion.hpp"

#include "../Map/TileMap.hpp"

using namespace std;

namespace Bomberman {
	const int Explosion::TTL = 1500;
	
	Explosion::Explosion(Coordinate position, int size) : position(position), _done(false) {
		Coordinate c;
		
		for (c.i = position.i - size, c.j = position.j; c.i <= position.i + size; ++c.i) {
			_hitArea.push_back(Coordinate(c));
		}
		
		for (c.i = position.i, c.j = position.j - size; c.j <= position.j + size; ++c.j) {
			if (c == position) {
				continue;
			}
			
			_hitArea.push_back(Coordinate(c));
		}
	}
	
	Explosion::~Explosion() {
		
	}
	
	void Explosion::update() {
		if (!timer.isCounting()) {
			timer.start();
		} else if (timer.getTime() >= TTL) {
			_done = true;
		}
	}
	
	bool Explosion::done() const {
		return _done;
	}
	
	vector<Coordinate> Explosion::hitArea() const {
		return _hitArea;
	}
}
