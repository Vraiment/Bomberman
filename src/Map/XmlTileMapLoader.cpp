//
//  XmlTileMapLoader.cpp
//  Bomberman
//
//  Created on 09/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "XmlTileMapLoader.hpp"

#include "../Elements/Brick.hpp"
#include "../Elements/Player.hpp"
#include "../Log/Log.hpp"
#include "../Log/LogLevel.hpp"
#include "../Utils/Exception.hpp"
#include "../Utils/OperatingSystem.hpp"
#include "TileMapBuilder.hpp"

using namespace std;
using namespace tinyxml2;

namespace Bomberman {
	class Builder : public TileMapBuilder {
	public:
		int _width = 0, _height = 0;
		string _name;
		vector<Brick> _bricks;
		shared_ptr<Player> _player;
		
		int width() const {
			return _width;
		}
		
		int height() const {
			return _height;
		}
		
		string name() const {
			return _name;
		}
		
		vector<Brick> bricks() const {
			return _bricks;
		}
		
		shared_ptr<Player> player() const {
			return _player;
		}
	};
	
	XmlTileMapLoader::~XmlTileMapLoader() {
		
	}
	
	std::shared_ptr<TileMapBuilder> XmlTileMapLoader::load(std::string fileName) {
		reset();
		
		this->fileName = fileName;
		string fullPath = getPath({"maps"}, fileName);
		
		if (document.LoadFile(fullPath.c_str()) == XML_NO_ERROR) {
			if (document.NoChildren()) {
				Log::get() << "Empty map file \"" << fileName << "\"." << LogLevel::error;
				_error = true;
			} else {
				loadDimension(document.RootElement());
				loadName(document.RootElement()->FirstChildElement("name"));
				loadPlayer(document.RootElement()->FirstChildElement("player"));
				loadBricks(document.RootElement()->FirstChildElement("bricks"));
			}
		} else {
			_error = true;
		}
		
		if (_error) {
			Log::get() << "Error loading map \"" << fileName << "\"." << OpeningFileErrorException();
			builder.reset();
		}
		
		return builder;
	}
	
	void XmlTileMapLoader::reset() {
		fileName.clear();
		document.Clear();
		_error = false;
		builder.reset(new Builder());
	}
	
	void XmlTileMapLoader::loadDimension(tinyxml2::XMLElement *root) {
		int width = 0;
		int height = 0;
		
		if (root->QueryIntAttribute("width", &width) != XML_NO_ERROR) {
			_error = true;
			Log::get() << "Invalid width in map file " << fileName << "." << LogLevel::error;
		}
		
		if (root->QueryIntAttribute("height", &height) != XML_NO_ERROR) {
			_error = true;
			Log::get() << "Invalid height in map file " << fileName << "." << LogLevel::error;
		}
		
		dynamic_pointer_cast<Builder>(builder)->_width = width;
		dynamic_pointer_cast<Builder>(builder)->_height = height;
	}
	
	void XmlTileMapLoader::loadName(XMLElement *nameNode) {
		if (nameNode == nullptr) {
			Log::get() << "No name in map file \"" << fileName << "\"." << LogLevel::error;
			_error = true;
		}
		
		dynamic_pointer_cast<Builder>(builder)->_name = nameNode->GetText();
	}
	
	void XmlTileMapLoader::loadPlayer(XMLElement *playerNode) {
		shared_ptr<Player> player(new Player());
		
		if (playerNode == nullptr) {
			Log::get() << "No information for player in map file \"" << fileName << "\"." << LogLevel::error;
			_error = true;
			return;
		}
		
		auto position = playerNode->FirstChildElement("position");
		if (position == nullptr) {
			Log::get() << "No position for player in map file \"" << fileName << "\"." << LogLevel::error;
			_error = true;
			return;
		}
		
		if (position->QueryIntAttribute("column", &player->position().i) != XML_NO_ERROR) {
			Log::get() << "Invalid column for player in map file \"" << fileName << "\"." << LogLevel::error;
			_error = true;
		}
		
		if (position->QueryIntAttribute("row", &player->position().j) != XML_NO_ERROR) {
			Log::get() << "Invalid row for player in map file \"" << fileName << "\"." << LogLevel::error;
			_error = true;
		}
		
		dynamic_pointer_cast<Builder>(builder)->_player = player;
	}
	
	void XmlTileMapLoader::loadBricks(XMLElement *bricks) {
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
				dynamic_pointer_cast<Builder>(builder)->_bricks.push_back(Brick(c, destructible));
			} else {
				_error |= error;
			}
			
			brick = brick->NextSiblingElement();
			++bricksCount;
		}
	}
}
