//
//  DummyTileMapBuilder.cpp
//  Bomberman
//
//  Created on 30/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#include "DummyTileMapBuilder.hpp"

#include "../Constants.hpp"
#include "../Elements/Brick.hpp"
#include "../Elements/Enemy.hpp"
#include "../Elements/Player.hpp"
#include "../Log/LogSystem.pch"
#include "../Utils/Exception.hpp"

using namespace std;
using namespace Bomberman::Constants;

namespace Bomberman {
	int DummyTileMapBuilder::width() const {
		return _width;
	}
	
	int DummyTileMapBuilder::height() const {
		return _height;
	}
	
	int DummyTileMapBuilder::enemyRange(string enemyType) const {
		if (ENEMY_EASY == enemyType) {
			return enemiesRange.easy;
		} else if (ENEMY_MEDIUM == enemyType) {
			return enemiesRange.medium;
		} else if (ENEMY_HARD == enemyType) {
			return enemiesRange.hard;
		}
		
		Log::get() << "Invalid enemy type: \"" << enemyType << "\"." << InvalidArgumentException();
		
		return -1;
	}
	
	int DummyTileMapBuilder::enemySpeed(string enemyType) const {
		if (ENEMY_EASY == enemyType) {
			return enemiesSpeed.easy;
		} else if (ENEMY_MEDIUM == enemyType) {
			return enemiesSpeed.medium;
		} else if (ENEMY_HARD == enemyType) {
			return enemiesSpeed.hard;
		}
		
		Log::get() << "Invalid enemy type: \"" << enemyType << "\"." << InvalidArgumentException();
		
		return -1;
	}
	
	string DummyTileMapBuilder::name() const {
		return _name;
	}
	
	vector<Brick> DummyTileMapBuilder::bricks() const {
		return _bricks;
	}
	
	vector<Enemy> DummyTileMapBuilder::enemies() const {
		return _enemies;
	}
	
	shared_ptr<Player> DummyTileMapBuilder::player() const {
		return _player;
	}
}
