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
#include <tinyxml2/tinyxml2.h>
#include "OperatingSystem.hpp"
#include "Texture.hpp"
#include "Brick.hpp"
#include "Exception.hpp"
#include "Log.hpp"
#include "Coordinate.hpp"

using namespace std;
using namespace tinyxml2;

namespace Bomberman {
	TileMap::TileMap(string fileName) : width(0), height(0) {
		throw NotImplementedException();
		
		file = getPath({ "maps", file });
		XMLDocument document;
		
		bool error = false;
		
		if (document.LoadFile(file.c_str()) == XML_NO_ERROR) {
			auto root = document.RootElement();
			
			error |= loadDimension(root);
			error |= loadName(root->FirstChildElement("name"));
			loadBricks(root->FirstChildElement("bricks"));
		} else {
			error = true;
		}
		
		if (error) {
			Log::get() << "Error loading map " << file << "." << OpeningFileErrorException();
		} else {
			Log::get() << "Loaded map " << file << " with name " << name << "." << LogLevel::info;
		}
	}
	
	TileMap::~TileMap() {
		
	}
	
	int TileMap::getWidth() const {
		return width;
	}
	
	int TileMap::getHeight() const {
		return height;
	}
	
	string TileMap::getName() const {
		return name;
	}
	
	vector<Brick> TileMap::getBricks() const {
		return bricks;
	}
	
	bool TileMap::loadDimension(void *e) {
		auto root = (XMLElement *) e;
		
		bool error = false;
		
		if (root->QueryIntAttribute("width", &width) != XML_NO_ERROR) {
			error = true;
			Log::get() << "Invalid width in map file " << file << "." << LogLevel::error;
		}
		
		if (root->QueryIntAttribute("height", &height) != XML_NO_ERROR) {
			error = true;
			Log::get() << "Invalid height in map file " << file << "." << LogLevel::error;
		}
		
		return error;
	}
	
	bool TileMap::loadName(void *e) {
		if (e == nullptr) {
			Log::get() << "No name in map file " << file << "." << LogLevel::error;
			return false;
		}
		
		auto name = (XMLElement *) e;
		
		this->name = name->GetText();
		
		return true;
	}
	
	void TileMap::loadBricks(void *e) {
		if (e == nullptr) {
			Log::get() << "No bricks node in map file " << file << "." << LogLevel::warning;
			return;
		}
		
		auto bricks = (XMLElement *) e;
		
		for (auto brick = bricks->FirstChildElement("brick"); brick; brick = brick->NextSiblingElement()) {
			Coordinate c;
			
			if (brick->QueryIntAttribute("column", &c.i) != XML_NO_ERROR) {
				Log::get() << "Invalid brick position in map file " << file << "." << LogLevel::error;
				continue;
			}
			
			if (brick->QueryIntAttribute("row", &c.j) != XML_NO_ERROR) {
				Log::get() << "Invalid brick row in map file " << file << "." << LogLevel::error;
				continue;
			}
			
			bool destructible = false;
			auto result = brick->QueryBoolAttribute("destructible", &destructible);
			if (result != XML_NO_ERROR && result != XML_NO_ATTRIBUTE) {
				Log::get() << "Invalid brick destructible value in map file " << file << ", using default." << LogLevel::warning;
			}
			
			addBrick(Brick(c, destructible));
		}
		
		return;
	}
	
	void TileMap::addBrick(Brick b) {
		bool found = false;
		
		for (int i = 0; i < bricks.size(); ++i) {
			if (bricks[i].position() == b.position()) {
				Log::get() << "Overwritting brick with position " << b.position().toString() << " in map file " << file << "." << LogLevel::warning;
				
				found = true;
				bricks[i] = b;
			}
		}
		
		if (!found) {
			bricks.push_back(b);
		}
	}
}
