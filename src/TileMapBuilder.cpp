//
//  TileMapBuilder.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "TileMapBuilder.hpp"

#include <tinyxml2/tinyxml2.h>
#include <SDL2_image/SDL_image.h>
#include <vector>
#include <sstream>

using namespace tinyxml2;
using namespace std;

namespace Bomberman {
	TileMapBuilder::TileMapBuilder(string fileName) : mapWidth(0), mapHeight(0) {
		XMLDocument file;
		
		if (file.LoadFile(fileName.c_str()) == XML_NO_ERROR) {
			Logger::log("Using map file \"" + fileName + "\".", LogLevel::info);
		} else {
			Logger::log("Could not open map file \"" + fileName + "\".", LogLevel::fatal);
		}
		
		auto root = file.RootElement();
		
		loadInfo(root);
		
		names = Matrix<string>(mapWidth, mapHeight);
		
		fillMatrix(root->FirstChildElement("tiles"));
	}
	
	int TileMapBuilder::getMapWidth() const {
		return mapWidth;
	}
	
	int TileMapBuilder::getMapHeight() const {
		return mapHeight;
	}
	
	int TileMapBuilder::getTexturesWidth() const {
		throw NotImplementedException();
	}
	
	int TileMapBuilder::getTexturesHeight() const {
		throw NotImplementedException();
	}
	
	string TileMapBuilder::getTextureName(int column, int row) const {
		return names.get(column, row);
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
	}
	
	void TileMapBuilder::fillMatrix(XMLElement *tiles) {
		if (tiles == nullptr) {
			return;
		}
		
		int column, row, result;
		Matrix<bool> done(mapWidth, mapHeight);
		stringstream logMsg;
		
		for (int i = 0; i < done.columns(); ++i) {
			for (int j = 0; j < done.rows(); ++j) {
				done.set(i, j, false);
			}
		}
		
		for (auto tile = tiles->FirstChildElement("tile"); tile != nullptr; tile = tile->NextSiblingElement("tile")) {
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
			
			if (!names.validPos(column, row)) {
				logMsg.clear();
				logMsg << "Invalid position (" << column << ", " << row << ") for a tile.";
				
				Logger::log(logMsg.str(), LogLevel::error);
				continue;
			}
			
			string name = tile->FirstChildElement("texture")->GetText();
			
			if (done.get(column, row)) {
				logMsg.clear();
				logMsg << "Overwritting texture \"" + names.get(column, row) + "\" ";
				logMsg << "in position (" << column << ", " << row << ").";
				
				Logger::log(logMsg.str(), LogLevel::warning);
			} else {
				done.set(column, row, true);
			}
			
			names.set(column, row, name);
		}
		
		for (int i = 0; i < done.columns(); ++i) {
			for (int j = 0; j < done.rows(); ++j) {
				if (!done.get(i, j)) {
					logMsg.clear();
					
					logMsg << "Tile (" << i << ", " << j << ") is empty.";
					Logger::log(logMsg.str(), LogLevel::warning);
				}
			}
		}
	}
}
