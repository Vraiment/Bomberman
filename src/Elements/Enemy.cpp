//
//  Enemy.cpp
//  Bomberman
//
//  Created on 30/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#include "Enemy.hpp"

#include "Player.hpp"
#include "../Map/TileMap.hpp"
#include "../Math/Random.hpp"

using namespace std;

namespace Bomberman {
	Enemy::Enemy(string type, Coordinate position) : type(type), position(position) {
		
	}
	
	string Enemy::getType() const {
		return type;
	}
	
	Coordinate Enemy::getPosition() const {
		return position;
	}
	
	void Enemy::setPosition(Coordinate position) {
		this->position = position;
	}
}
