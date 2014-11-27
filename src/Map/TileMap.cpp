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

#include "../Elements/Bomb.hpp"
#include "../Elements/Brick.hpp"
#include "../Elements/Explosion.hpp"
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
			
			if (!_area.contains(brick->position()))
			{
				Log::get() << "Brick out of map at position: " << brick->position().toString() << "." << LogLevel::warning;
				continue;
			}
			
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
	
	list<Bomb> TileMap::bombs() const {
		return _bombs;
	}
	
	vector<Brick> TileMap::bricks() const {
		return _bricks;
	}
	
	list<Explosion> TileMap::explosions() const {
		return _explosions;
	}
	
	shared_ptr<Player> TileMap::player() const {
		return _player;
	}
	
	void TileMap::update() {
		vector<Coordinate> goneBombs = updateBombs();
		updateExplosions(goneBombs);
	}
	
	void TileMap::addBomb(Bomb bomb) {
		_bombs.push_back(bomb);
	}
	
	bool TileMap::tileHasBrick(Coordinate tile) const {
		for (auto brick = _bricks.begin(); brick != _bricks.end(); ++brick) {
			if (brick->position() == tile) {
				return true;
			}
		}
		
		return false;
	}
	
	bool TileMap::tileHasBomb(Coordinate tile) const {
		for (auto it = _bombs.begin(); it != _bombs.end(); ++it) {
			if (it->getPosition() == tile) {
				return true;
			}
		}
		
		return false;
	}
	
	vector<Coordinate> TileMap::updateBombs() {
		vector<Coordinate> goneBombs;
		
		for (auto bomb = _bombs.begin(); bomb != _bombs.end(); ++bomb) {
			bomb->update();
			
			if (bomb->exploded()) {
				goneBombs.push_back(bomb->getPosition());
			}
		}
		
		_bombs.remove_if([](Bomb bomb) { return bomb.exploded(); });
		
		return goneBombs;
	}
	
	void TileMap::updateExplosions(vector<Coordinate> newExplosions) {
		for (auto it = newExplosions.begin(); it != newExplosions.end(); ++it) {
			Explosion e(*it, _player->getExplosionSize());
			_explosions.push_back(e);
		}
		
		for (auto it = _explosions.begin(); it != _explosions.end(); ++it) {
			it->update();
		}
		
		_explosions.remove_if([](Explosion explosion) { return explosion.done(); });
	}
}
