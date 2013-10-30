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
#include "../tinyxml2/tinyxml2.h"

namespace Bomberman {
	TileMapBuilder::TileMapBuilder(std::string fileName) {
		tinyxml2::XMLDocument file;
		
		file.LoadFile(fileName.c_str());
	}
	
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
