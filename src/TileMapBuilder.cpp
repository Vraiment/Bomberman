//
//  TileMapBuilder.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "TileMapBuilder.hpp"

#include "Texture.hpp"
#include "NotImplementedException.hpp"

namespace Bomberman {
	int TileMapBuilder::getMapWidth() const {
		return mapWidth;
	}
	
	int TileMapBuilder::getMapHeight() const {
		return mapHeight;
	}
	
	Texture TileMapBuilder::getTexture(int column, int row) const {
		throw NotImplementedException();
	}
}
