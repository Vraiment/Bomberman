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
#include "../Utils/VectorUtils.hpp"

#include <array>
#include <climits>

using namespace std;

namespace Bomberman {
	bool validNewPosition(shared_ptr<TileMap> tileMap, Coordinate position) {
		return tileMap->area().contains(position) && !tileMap->tileHasBomb(position) && !tileMap->tileHasBrick(position);
	}
	
	Enemy::Enemy(string type, Coordinate position) : type(type), position(position), speed(INT_MAX) {
		timer.start();
	}
	
	void Enemy::update(std::shared_ptr<TileMap> tileMap) {
		if (timer.getTime() >= speed) {
			randomMove(tileMap);
			
			timer.clear();
			timer.start();
		}
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
	
	void Enemy::setSpeed(int speed) {
		this->speed = speed;
	}
	
	void Enemy::randomMove(shared_ptr<TileMap> tileMap) {
		vector<Coordinate> availablePositions;
		
		array<Coordinate, 4> adjacents = position.cross();
		for (Coordinate adjacent : adjacents) {
			if (validNewPosition(tileMap, adjacent)) {
				availablePositions.push_back(adjacent);
			}
		}
		
		if (availablePositions.empty()) {
			return;
		}
		
		position = VectorUtils::randomElement(availablePositions);
	}
}
