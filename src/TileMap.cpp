//
//  TileMap.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "TileMap.hpp"
#include "Texture.hpp"

#include <SDL2/SDL.h>

namespace Bomberman {
	TileMap::TileMap(TileMapBuilder *builder) {
		width = builder->getMapWidth();
		height = builder->getMapHeight();
		
		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				tileTextures.push_back(builder->getTexture(i, j));
			}
		}
	}
	
	int TileMap::getWidth() const {
		return width;
	}
	
	int TileMap::getHeight() const {
		return height;
	}
	
	Texture TileMap::getTileTexture(int i, int j) const {
		return tileTextures[i + (j * width)];
	}
}
