//
//  TileMap.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "TileMap.hpp"

#include <SDL2/SDL.h>

namespace Bomberman {
	TileMap::TileMap(ITileMapBuilder *builder) {
		width = builder->width();
		height = builder->height();
		total = width * height;
		
		textures = new SDL_Texture*[total];
		
		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				textures[i + (j * width)] = builder->getTexture(i, j);
			}
		}
	}
	
	TileMap::~TileMap() {
		for (int n = 0; n < total; ++n) {
			SDL_DestroyTexture(textures[n]);
		}
		
		delete[] textures;
	}
	
	int TileMap::getWidth() const {
		return width;
	}
	
	int TileMap::getHeight() const {
		return height;
	}
}
