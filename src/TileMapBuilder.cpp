//
//  TileMapBuilder.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "TileMapBuilder.hpp"

#include "Texture.hpp"
#include <tinyxml2/tinyxml2.h>
#include <SDL2_image/SDL_image.h>
#include <map>

using namespace tinyxml2;
using namespace std;

namespace Bomberman {
	TileMapBuilder::TileMapBuilder(string fileName, Renderer renderer) : mapWidth(0), mapHeight(0) {
		XMLDocument file;
		
		file.LoadFile(fileName.c_str());
		
		XMLElement *root = file.RootElement();
		
		XMLElement *name = root->FirstChildElement("name");
		XMLElement *textures = root->FirstChildElement("textures");
		XMLElement *tiles = root->FirstChildElement("tiles");
		
		mapName = name->GetText();
		root->QueryIntAttribute("width", &mapWidth);
		root->QueryIntAttribute("height", &mapHeight);
		
		std::map<int, Texture> texturesMap;
		
		for (XMLElement *texture = textures->FirstChildElement(); texture != nullptr; texture = texture->NextSiblingElement()) {
			int textureId = 0;
			texture->QueryIntAttribute("id", &textureId);

			texturesMap[textureId] = Texture(texture->GetText(), renderer);
		}
		
		for (XMLElement *tile = tiles->FirstChildElement(); tile != nullptr; tile = tile->NextSiblingElement()) {
			int tileCol = 0;
			int tileRow = 0;
			
			tile->QueryIntAttribute("column", &tileCol);
			tile->QueryIntAttribute("row", &tileRow);
			
			string textureId = tile->FirstChildElement("texture")->GetText();
			
			tileTextures.set(tileCol, tileRow, texturesMap[stoi(textureId)]);
		}
	}
	
	int TileMapBuilder::getMapWidth() const {
		return mapWidth;
	}
	
	int TileMapBuilder::getMapHeight() const {
		return mapHeight;
	}
	
	Texture TileMapBuilder::getTexture(int column, int row) const {
		return tileTextures.get(column, row);
	}
}
