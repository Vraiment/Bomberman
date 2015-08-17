//
//  Player.cpp
//  Bomberman
//
//  Created on 12/6/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Player.hpp"

#include "Item.hpp"

namespace Bomberman {
	const int Player::invincibleTime = 750;
	
	Player::Player() : explosionSize(1), _maxBombs(1), dead(false) {
		
	}
	
	Coordinate& Player::position() {
		return _position;
	}
	
	void Player::update() {
		if (invincible.isCounting() && invincible.getTime() >= invincibleTime) {
			invincible.stop();
		}
	}
	
	void Player::addItem(Item item) {
		if (item == Item::EXTRA_BOMB) {
			++_maxBombs;
		} else if (item == Item::INCREASE_RANGE) {
			++explosionSize;
		} else {
			Log::get() << "Player tried to process invalid item with id: " << item.id() << LogLevel::error;
		}
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
	
	bool Player::isInvincible() const {
		return invincible.isCounting();
	}
	
	void Player::die() {
		dead = true;
	}
	
	void Player::respawn() {
		dead = false;
		
        invincible.restart();
	}
}
