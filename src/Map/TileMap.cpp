//
//  TileMap.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "TileMap.hpp"

#include <SDL2/SDL.h>
#include <tinyxml2/tinyxml2.h>

#include "../Elements/Brick.hpp"
#include "../Elements/Player.hpp"
#include "../Log/Log.hpp"
#include "../Log/LogLevel.hpp"
#include "../Utils/Exception.hpp"
#include "TileMapBuilder.hpp"

using namespace std;
using namespace tinyxml2;

namespace Bomberman {
	TileMap::TileMap(shared_ptr<TileMapBuilder> builder) {
		if (!builder) {
			Log::get() << "Invalid information to create map." << NullArgumentException();
		}
		
		if (builder->width() > 0) {
			_area.width = builder->width();
		} else {
			Log::get() << "Invalid width for map." << LogLevel::error;
		}
		
		if (builder->height() > 0) {
			_area.height = builder->height();
		} else {
			Log::get() << "Invalid height for map." << LogLevel::error;
		}
		
		if (!builder->name().empty()) {
			_name = builder->name();
		} else {
			Log::get() << "Empty name for map." << LogLevel::warning;
		}
		
		if (builder->player()) {
			_player = builder->player();
		} else {
			Log::get() << "No player information for map." << LogLevel::error;
			_player.reset(new Player());
		}
		
		auto bricks = builder->bricks();
		for (auto brick = bricks.begin(); brick != bricks.end(); ++brick) {
			bool found = false;
			
			for (int n = 0; n < _bricks.size(); ++n) {
				if (brick->position() == _bricks[n].position()) {
					Log::get() << "Duplicate bricks with the same position: " << brick->position().toString() << "."  << LogLevel::warning;
					
					_bricks[n] = *brick;
					found = true;
				}
			}
			
			if (!found) {
				_bricks.push_back(*brick);
			}
		}
	}
	
	TileMap::~TileMap() {
		
	}
	
	Rectangle TileMap::area() const {
		return _area;
	}
	
	int TileMap::width() const {
		return _area.width;
	}
	
	int TileMap::height() const {
		return _area.height;
	}
	
	string TileMap::name() const {
		return _name;
	}
	
	vector<Brick> TileMap::bricks() const {
		return _bricks;
	}
	
	shared_ptr<Player> TileMap::player() const {
		return _player;
	}
	
	void TileMap::update() {
		
	}
}
