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
#include <sstream>

using namespace tinyxml2;
using namespace std;

namespace Bomberman {
	TileMapBuilder::TileMapBuilder(string fileName, Renderer renderer) : mapWidth(0), mapHeight(0), renderer(renderer) {
		XMLDocument file;
		
		if (file.LoadFile(fileName.c_str()) != XML_NO_ERROR) {
			Logger::log("Using map file \"" + fileName + "\".", LogLevel::info);
		} else {
			Logger::log("Could not open map file \"" + fileName + "\".", LogLevel::error);
			
			return;
		}
		
		XMLElement *root = file.RootElement();
		
		loadInfo(root);
		
		map<int, Texture> textures = loadTextures(root->FirstChildElement("textures"));
		
		setTextures(root->FirstChildElement("tiles"), textures);
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
	
	void TileMapBuilder::loadInfo(XMLElement *root) {
		XMLElement *name = root->FirstChildElement("name");
		
		if (name != nullptr) {
			mapName = name->GetText();
		} else {
			Logger::log("Map name not found.", LogLevel::warning);
		}
		
		int result;
		
		result = root->QueryIntAttribute("width", &mapWidth);
		if ((result == XML_NO_ERROR && mapWidth < 0) || result == XML_WRONG_ATTRIBUTE_TYPE) {
			Logger::log("Bad map width.", LogLevel::error);
		} else if (result == XML_NO_ATTRIBUTE) {
			Logger::log("No width found for map.", LogLevel::error);
		}
		
		result = root->QueryIntAttribute("height", &mapHeight);
		if ((result == XML_NO_ERROR && mapHeight < 0) || result == XML_WRONG_ATTRIBUTE_TYPE) {
			Logger::log("Bad map height.", LogLevel::error);
		} else if (result == XML_NO_ATTRIBUTE) {
			Logger::log("No height found for map.", LogLevel::error);
		}
		
		tileTextures = Matrix<Texture>(mapWidth, mapHeight);
	}
	
	map<int, Texture> TileMapBuilder::loadTextures(XMLElement *node) {
		map<int, Texture> textures;
		
		if (node == nullptr) {
			return textures;
		}
		
		for (XMLElement *texture = node->FirstChildElement("texture"); texture != nullptr; texture = texture->NextSiblingElement("texture")) {
			string textureName = texture->GetText();

			int textureId = 0;
			int result = texture->QueryIntAttribute("id", &textureId);
			if (result == XML_WRONG_ATTRIBUTE_TYPE) {
				Logger::log("Invalid texture id for texture \"" + textureName + "\".", LogLevel::error);
			 
				continue;
			} else if (result == XML_NO_ATTRIBUTE) {
				Logger::log("Texture \"" + textureName + "\" has no name.", LogLevel::error);
			}

			if (textures.find(textureId) != textures.end()) {
				stringstream warning;
				warning << "Overwritting texture with id " << textureId << ".";

				Logger::log(warning.str(), LogLevel::warning);
			}

			textures[textureId] = Texture(texture->GetText(), renderer);
		}
		
		return textures;
	}
	
	void TileMapBuilder::setTextures(XMLElement *tiles, map<int, Texture> textures) {
		if (tiles == nullptr) {
			return;
		}
		
		int column, row, result;
		
		for (XMLElement *tile = tiles->FirstChildElement("tile"); tile != nullptr; tile = tile->NextSiblingElement("tile")) {
			result = tile->QueryIntAttribute("column", &column);
			if (result == XML_WRONG_ATTRIBUTE_TYPE) {
				Logger::log("Invalid column value for a tile.", LogLevel::error);
				continue;
			} else if (result == XML_NO_ATTRIBUTE) {
				Logger::log("No column value for a tile.", LogLevel::error);
				continue;
			}
			
			tile->QueryIntAttribute("row", &row);
			if (result == XML_WRONG_ATTRIBUTE_TYPE) {
				Logger::log("Invalid row value for a tile.", LogLevel::error);
				continue;
			} else if (result == XML_NO_ATTRIBUTE) {
				Logger::log("No row value for a tile.", LogLevel::error);
				continue;
			}
			
			if (!tileTextures.validPos(column, row)) {
				stringstream error;
				error << "Invalid position (" << column << ", " << row << ") for a tile.";
				
				Logger::log(error.str(), LogLevel::error);
			}
			
			string idString = tile->FirstChildElement("texture")->GetText();
			int id;
			bool error = false;
			try {
				id = stoi(idString);
				continue;
			} catch (...) {
				error = true;
			}
			
			error |= textures.find(id) == textures.end();
			
			if (error) {
				stringstream error;
				error << "Invalid texture id for tile (" << column << ", " << row << ").";
				
				Logger::log(error.str(), LogLevel::error);
				continue;
			}
			
			tileTextures.set(column, row, textures[id]);
		}
	}
}
