//
//  TileMapLoader.cpp
//  Bomberman
//
//  Created on 09/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "TileMapLoader.hpp"

#include "../Elements/Brick.hpp"
#include "../Elements/Player.hpp"
#include "../Log/Log.hpp"
#include "../Log/LogLevel.hpp"
#include "../Utils/Exception.hpp"
#include "../Utils/OperatingSystem.hpp"
#include "TileMap.hpp"

using namespace std;
using namespace tinyxml2;

namespace Bomberman {
	TileMapLoader::~TileMapLoader() {
		
	}
	
	shared_ptr<TileMap> TileMapLoader::load(std::string fileName) {
		reset();
		
		this->fileName = fileName;
		string fullPath = getPath({"maps"}, fileName);
		
		if (document.LoadFile(fullPath.c_str()) == XML_NO_ERROR) {
			if (document.NoChildren()) {
				Log::get() << "Empty map file \"" << fileName << "\"." << LogLevel::error;
			} else {
				loadDimension(document.RootElement());
				loadName(document.RootElement()->FirstChildElement("name"));
				loadPlayer(document.RootElement()->FirstChildElement("player"));
				loadBricks(document.RootElement()->FirstChildElement("bricks"));
			}
		} else {
			error = true;
		}
		
		if (error) {
			Log::get() << "Error loading map \"" << fileName << "\"." << OpeningFileErrorException();
		}
		
		return tileMap;
	}
	
	void TileMapLoader::reset() {
		fileName.clear();
		document.Clear();
		error = false;
		tileMap.reset(new TileMap());
	}
	
	void TileMapLoader::loadDimension(tinyxml2::XMLElement *root) {
		if (root->QueryIntAttribute("width", &tileMap->_width) != XML_NO_ERROR) {
			error = true;
			Log::get() << "Invalid width in map file " << fileName << "." << LogLevel::error;
		}
		
		if (root->QueryIntAttribute("height", &tileMap->_height) != XML_NO_ERROR) {
			error = true;
			Log::get() << "Invalid height in map file " << fileName << "." << LogLevel::error;
		}
	}
	
	void TileMapLoader::loadName(XMLElement *name) {
		if (name == nullptr) {
			Log::get() << "No name in map file \"" << fileName << "\"." << LogLevel::error;
			error = true;
		}
		
		tileMap->_name = name->GetText();
	}
	
	void TileMapLoader::loadPlayer(XMLElement *player) {
		if (player == nullptr) {
			Log::get() << "No information for player in map file \"" << fileName << "\"." << LogLevel::error;
			error = true;
			return;
		}
		
		auto position = player->FirstChildElement("position");
		if (position == nullptr) {
			Log::get() << "No position for player in map file \"" << fileName << "\"." << LogLevel::error;
			error = true;
			return;
		}
		
		if (position->QueryIntAttribute("column", &tileMap->player()->position().i) != XML_NO_ERROR) {
			Log::get() << "Invalid column for player in map file \"" << fileName << "\"." << LogLevel::error;
			error = true;
		}
		
		if (position->QueryIntAttribute("row", &tileMap->player()->position().j) != XML_NO_ERROR) {
			Log::get() << "Invalid row for player in map file \"" << fileName << "\"." << LogLevel::error;
			error = true;
		}
	}
	
	void TileMapLoader::loadBricks(XMLElement *bricks) {
		if (bricks == nullptr) {
			Log::get() << "No bricks node in map file " << fileName << "." << LogLevel::warning;
			return;
		}
		
		int bricksCount = 1;
		auto brick = bricks->FirstChildElement("brick");
		bool error;
		while (brick) {
			error = false;
			
			Coordinate c;
			if (brick->QueryIntAttribute("column", &c.i) != XML_NO_ERROR) {
				Log::get() << "Brick number " << bricksCount << " has invalid column in map file \"" << fileName << "\"." << LogLevel::error;
				error = true;
			}
			
			if (brick->QueryIntAttribute("row", &c.j) != XML_NO_ERROR) {
				Log::get() << "Brick number " << bricksCount << " has invalid row in map file \"" << fileName << "\"." << LogLevel::error;
				error = true;
			}
			
			bool destructible = false;
			auto result = brick->QueryBoolAttribute("destructible", &destructible);
			if (result != XML_NO_ERROR && result != XML_NO_ATTRIBUTE) {
				Log::get() << "Brick number " << bricksCount << " has invalid \"destructible\" value in map file \"" << fileName << "\", using default value." << LogLevel::warning;
			}
			
			if (!error) {
				addBrick(bricksCount, Brick(c, destructible));
			}
			
			brick = brick->NextSiblingElement();
			++bricksCount;
		}
	}
	
	void TileMapLoader::addBrick(int number, Brick brick) {
		Rectangle area(0, 0, tileMap->_width, tileMap->_height);
		
		if (!area.contains(brick.position())) {
			Log::get() << "Brick number " << number << " out of map area in map file \"" << fileName << "\"." << LogLevel::error;
			return;
		}
		
		for (int n = 0; n < tileMap->_bricks.size(); ++n) {
			if (tileMap->_bricks[n].position() == brick.position()) {
				Log::get() << "Brick number " << number << " has duplicate position " << brick.position().toString() << " in map file \"" << fileName << "\"." << LogLevel::warning;
				
				tileMap->_bricks[n] = brick;
				return;
			}
		}
		
		tileMap->_bricks.push_back(brick);
	}
}
