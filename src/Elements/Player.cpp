//
//  Player.cpp
//  Bomberman
//
//  Created on 12/6/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Player.hpp"

#include "Item.hpp"
#include "../Log/LogSystem.pch"

namespace Bomberman {
	const int Player::invincibleTime = 750;
	
	Player::Player() : explosionSize(1), _maxBombs(1), dead(false), _isInvincible(false) {
		
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
	
    void Player::setInvincibility(bool invincible) {
        _isInvincible = invincible;
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
        return _isInvincible || invincible.isCounting();
	}
	
	void Player::die() {
		dead = true;
	}
	
	void Player::respawn() {
		dead = false;
		
        invincible.restart();
	}
}
