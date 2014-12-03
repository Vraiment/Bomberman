//
//  DummyTileMapBuilder.cpp
//  Bomberman
//
//  Created on 30/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#include "DummyTileMapBuilder.hpp"

#include "../Elements/Brick.hpp"
#include "../Elements/Enemy.hpp"
#include "../Elements/Player.hpp"

using namespace std;

namespace Bomberman {
	int DummyTileMapBuilder::width() const {
		return _width;
	}
	
	int DummyTileMapBuilder::height() const {
		return _height;
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
