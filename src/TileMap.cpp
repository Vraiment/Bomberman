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
	TileMap::TileMap() : width(0), height(0) {
		
	}
	
	void TileMap::createFrom(TileMapBuilder builder, shared_ptr<SDL_Renderer> renderer) {
		width = builder.getMapWidth();
		height = builder.getMapHeight();
		
		texturesWidth = builder.getTexturesWidth();
		texturesHeight = builder.getTexturesHeight();
		
		tileTextures = Matrix<Texture>(width, height);
		map<string, Texture> textures;
		
		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				string textureName = builder.getTextureName(i, j);
				auto textureInMap = textures.find(textureName);
				
				Texture texture;
				if (textureInMap != textures.end()) {
					texture = textureInMap->second;
				} else {
					texture = Texture(textureName, renderer);
					textures[textureName] = texture;
				}
				
				tileTextures.set(i, j, texture);
			}
		}
	}
	
	int TileMap::getWidth() const {
		return width;
	}
	
	int TileMap::getHeight() const {
		return height;
	}
	
	int TileMap::getTexturesWidth() const {
		return texturesWidth;
	}
	
	int TileMap::getTexturesHeight() const {
		return texturesHeight;
	}
	
	Texture TileMap::getTileTexture(int i, int j) const {
		return tileTextures.get(i, j);
	}
}
