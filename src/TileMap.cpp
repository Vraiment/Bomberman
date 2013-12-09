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
	TileMap::TileMap(string fileName) : rectangle() {
		file = getPath({ "maps" }, fileName);
		XMLDocument document;
		
		bool error = false;
		
		if (document.LoadFile(file.c_str()) == XML_NO_ERROR) {
			auto root = document.RootElement();
			
			error |= !loadDimension(root);
			error |= !loadName(root->FirstChildElement("name"));
			error |= !loadPlayer(root->FirstChildElement("player"));
			loadBricks(root->FirstChildElement("bricks"));
		} else {
			error = true;
		}
		
		if (error) {
			Log::get() << "Error loading map " << file << "." << OpeningFileErrorException();
		} else {
			Log::get() << "Loaded map " << file << " with name " << _name << "." << LogLevel::info;
		}
	}
	
	TileMap::~TileMap() {
		
	}
	
	int TileMap::width() const {
		return rectangle.width;
	}
	
	int TileMap::height() const {
		return rectangle.height;
	}
	
	string TileMap::name() const {
		return _name;
	}
	
	vector<Brick> TileMap::bricks() const {
		return _bricks;
	}
	
	Player TileMap::player() const {
		return _player;
	}
	
	bool TileMap::loadDimension(void *e) {
		auto root = (XMLElement *) e;
		
		bool valid = true;
		
		if (root->QueryIntAttribute("width", &rectangle.width) != XML_NO_ERROR) {
			valid = false;
			Log::get() << "Invalid width in map file " << file << "." << LogLevel::error;
		}
		
		if (root->QueryIntAttribute("height", &rectangle.height) != XML_NO_ERROR) {
			valid = false;
			Log::get() << "Invalid height in map file " << file << "." << LogLevel::error;
		}
		
		return valid;
	}
	
	bool TileMap::loadName(void *e) {
		if (e == nullptr) {
			Log::get() << "No name in map file " << file << "." << LogLevel::error;
			return false;
		}
		
		auto name = (XMLElement *) e;
		
		this->_name = name->GetText();
		
		return true;
	}
	
	bool TileMap::loadPlayer(void *e) {
		if (e == nullptr) {
			Log::get() << "No information for player in map file " << file << "." << LogLevel::error;
			return false;
		}
		
		bool valid = true;
		
		auto player = (XMLElement *) e;
		auto position = player->FirstChildElement("position");
		
		if (position == nullptr) {
			Log::get() << "No position for player in map file " << file << "." << LogLevel::error;
		}
		
		if (position->QueryIntAttribute("column", &_player.position().i) != XML_NO_ERROR) {
			Log::get() << "Invalid column for player in map file " << file << "." << LogLevel::error;
			valid = false;
		}
		
		if (position->QueryIntAttribute("row", &_player.position().j) != XML_NO_ERROR) {
			Log::get() << "Invalid row for player in map file " << file << "." << LogLevel::error;
			valid = false;
		}
		
		return valid;
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
				Log::get() << "Invalid brick column in map file " << file << "." << LogLevel::error;
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
		
		if (!rectangle.contains(b.position())) {
			Log::get() << "Brick out of range in position " << b.position().toString() << " in map file " << file << "." << LogLevel::error;
			return;
		}
		
		for (int i = 0; i < _bricks.size(); ++i) {
			if (_bricks[i].position() == b.position()) {
				Log::get() << "Overwritting brick with position " << b.position().toString() << " in map file " << file << "." << LogLevel::warning;
				
				found = true;
				_bricks[i] = b;
			}
		}
		
		if (!found) {
			_bricks.push_back(b);
		}
	}
}
