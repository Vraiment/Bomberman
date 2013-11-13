//
//  TileMap.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "TileMap.hpp"

#include <map>
#include <SDL2/SDL.h>
#include "Texture.hpp"

using namespace std;

namespace Bomberman {
	TileMap::TileMap(string fileName) : width(0), height(0) {
		
	}
	
	int TileMap::getWidth() const {
		return width;
	}
	
	int TileMap::getHeight() const {
		return height;
	}
	
	vector<Coordinate> TileMap::spawnPoints() const {
		return _spawnPoints;
	}
	
	vector<Coordinate> TileMap::bricks() const {
		return _bricks;
	}
	
	vector<Coordinate> TileMap::destructibleBricks() const {
		return _destructibleBricks;
	}
}
