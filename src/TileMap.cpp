//
//  TileMap.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "TileMap.hpp"

#include <SDL2/SDL.h>
#include <tinyxml2/tinyxml2.h>

#include "Elements/Brick.hpp"
#include "Log/Log.hpp"
#include "Log/LogLevel.hpp"
#include "Utils/Exception.hpp"
#include "Utils/OperatingSystem.hpp"

using namespace std;
using namespace tinyxml2;

namespace Bomberman {
	TileMap::TileMap() : _width(0), _height(0), _player(new Player()) {
		
	}
	
	TileMap::~TileMap() {
		
	}
	
	int TileMap::width() const {
		return _width;
	}
	
	int TileMap::height() const {
		return _height;
	}
	
	string TileMap::name() const {
		return _name;
	}
	
	vector<Brick> TileMap::bricks() const {
		return _bricks;
	}
	
	shared_ptr<Player> TileMap::player() const {
		return _player;
	}
	
	void TileMap::execute(string command) {
		throw NotImplementedException();		
	}
	
	void TileMap::update() {
		commandQueue.update();
	}
}
