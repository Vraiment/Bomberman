//
//  Player.cpp
//  Bomberman
//
//  Created on 12/6/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Player.hpp"

namespace Bomberman {
	Player::Player() : explosionSize(1), _maxBombs(1), dead(false) {
		
	}
	
	Coordinate& Player::position() {
		return _position;
	}
	
	int Player::getExplosionSize() const {
		return explosionSize;
	}
	
	int Player::maxBombs() const {
		return _maxBombs;
	}
	
	bool Player::isDead() const {
		return dead;
	}
	
	void Player::die() {
		dead = true;
	}
	
	void Player::respawn() {
		dead = false;
	}
}
