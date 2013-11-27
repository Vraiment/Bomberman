//
//  Viewport.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Viewport.hpp"

#include "Exception.hpp"
#include "TileMap.hpp"

using namespace std;

namespace Bomberman {
	Viewport::Viewport(int width, int height, string name) : Screen(width, height, name), _origin() {
	}
	
	Viewport::~Viewport() {
		
	}
	
	void Viewport::draw() {
		if (!shouldDraw()) {
			return;
		}
		
		drawBorder();
	}
	
	void Viewport::loadTileMap(shared_ptr<TileMap> tileMap) {
		this->tileMap = tileMap;
	}
	
	Coordinate& Viewport::origin() {
		return _origin;
	}
	
	bool Viewport::shouldDraw() {
		return
			tileMap &&
			tileMap->getWidth() > 1 &&
			tileMap->getHeight() > 1
		;
	}
	
	void Viewport::drawBorder() {
		throw NotImplementedException();
	}
}
