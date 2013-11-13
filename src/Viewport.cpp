//
//  Viewport.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Viewport.hpp"

#include "TileMap.hpp"

using namespace std;

namespace Bomberman {
	Viewport::Viewport(int width, int height, string name) : Screen(width, height, name), _origin() {
		
	}
	
	void Viewport::draw() {
		throw NotImplementedException();
	}
	
	void Viewport::loadTileMap(const TileMap& tileMap) {
		bricks = tileMap.bricks();
		destrutibleBricks = tileMap.destructibleBricks();
	}
	
	Coordinate& Viewport::origin() {
		return _origin;
	}
}
