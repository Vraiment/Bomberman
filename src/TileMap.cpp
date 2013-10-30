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
	TileMap::TileMap(ITileMapBuilder *builder) {
		width = builder->width();
		height = builder->height();
		total = width * height;
		
		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				tiles.push_back(builder->getTexture(i, j));
			}
		}
	}
	
	int TileMap::getWidth() const {
		return width;
	}
	
	int TileMap::getHeight() const {
		return height;
	}
	
	void TileMap::draw(SDL_Renderer *renderer) {
		for (int n = 0; n < tiles.size(); ++n) {
			tiles[n].draw(renderer);
		}
	}
}
