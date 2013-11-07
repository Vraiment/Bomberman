//
//  Viewport.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Viewport.hpp"

using namespace std;

namespace Bomberman {
	Viewport::Viewport(int width, int height, string name) : Screen(width, height, name), count(), _origin() {
		
	}
	
	void Viewport::draw() {
		Coordinate current = _origin;
		
		for (int j = 0; j < count.j; ++j, current.j += tileMap.getHeight()) {
			for (int i = 0; i < count.i; ++i, current.i += tileMap.getHeight()) {
				if (!validCoordinate(current)) {
					continue;
				}
				
				tileMap.getTileTexture(i, j).draw(current.i, current.j);
			}
		}
	}
	
	void Viewport::widthChanged(int prevWidth) {
		count.i = getWidth() / tileMap.getTexturesWidth();
	}
	
	void Viewport::heightChanged(int prevHeight) {
		count.j = getHeight() / tileMap.getHeight();
	}
	
	void Viewport::setTileMap(TileMap tileMap) {
		this->tileMap = tileMap;
		
		widthChanged(0);
		heightChanged(0);
	}
	
	Coordinate& Viewport::origin() {
		return _origin;
	}
	
	bool Viewport::validCoordinate(Coordinate coordinate) {
		return (0 <= coordinate.i) && (coordinate.i < getWidth()) && (0 <= coordinate.j) && (coordinate.j < getHeight());
	}
}
