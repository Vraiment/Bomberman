//
//  TileMap.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "TileMap.hpp"

#include <stack>
#include <SDL2/SDL.h>
#include <tinyxml2/tinyxml2.h>

#include "../Constants.hpp"
#include "../Elements/Bomb.hpp"
#include "../Elements/Brick.hpp"
#include "../Elements/Enemy.hpp"
#include "../Elements/Explosion.hpp"
#include "../Elements/Player.hpp"
#include "../Log/Log.hpp"
#include "../Log/LogLevel.hpp"
#include "../Utils/Exception.hpp"
#include "../Utils/VectorUtils.hpp"
#include "TileMapBuilder.hpp"

using namespace std;
using namespace tinyxml2;
using namespace Bomberman::Constants;

namespace Bomberman {
	const int TileMap::playerRespawnTime = 2000;
	
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
		
		vector<Enemy> enemies = builder->enemies();
		for (auto enemy : enemies) {
			if (!_area.contains(enemy.getPosition())) {
				Log::get() << "Enemy out of map at position: " << enemy.getPosition().toString() << "." << LogLevel::warning;
				continue;
			}
			
			if (tileHasBrick(enemy.getPosition())) {
				Log::get() << "Enemy overlapping a brick at position: " << enemy.getPosition().toString() << "." << LogLevel::warning;
				continue;
			}
			
			enemy.setSpeed(builder->enemySpeed(enemy.getType()));
			enemy.setRange(builder->enemyRange(enemy.getType()));
			
			_enemies.push_back(enemy);
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
	
	list<Enemy> TileMap::enemies() const {
		return _enemies;
	}
	
	list<Explosion> TileMap::explosions() const {
		return _explosions;
	}
	
	shared_ptr<Player> TileMap::player() const {
		return _player;
	}
	
	void TileMap::update() {
		updateEnemies();
		updateBombs();
		
		stack<Coordinate> blownBombs;
		do {
			_bombs.remove_if([&blownBombs] (Bomb bomb) {
				if (bomb.exploded()) {
					blownBombs.push(bomb.getPosition());
				}
				
				return bomb.exploded();
			});
			
			while (!blownBombs.empty()) {
				auto position = blownBombs.top();
				blownBombs.pop();
				
				Explosion explosion(position, _player->getExplosionSize());
				_explosions.push_back(explosion);
			}
			
			for (Explosion& explosion : _explosions) {
				doDamage(explosion.hitArea());
			}
		} while(!blownBombs.empty());
		
		updateExplosions();
		clearExplosions();
		
		if (_player->isDead() && playerRespawn.getTime() >= playerRespawnTime) {
			_player->respawn();
			playerRespawn.stop();
		}
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
	
	void TileMap::updateEnemies() {
		shared_ptr<TileMap> ptr = shared_from_this();
		
		for (auto& enemy : _enemies) {
			enemy.update(ptr);
		}
	}
	
	void TileMap::updateBombs() {
		for (Bomb& bomb : _bombs) {
			bomb.update();
		}
	}
	
	int TileMap::bombCount() const {
		return (int)_bombs.size();
	}
	
	void TileMap::doDamage(vector<Coordinate> hitArea) {
		for (Coordinate position : hitArea) {
			for (Bomb& bomb : _bombs) {
				if (position == bomb.getPosition()) {
					bomb.forceExplosion();
					break;
				}
			}
			
			_enemies.remove_if([position] (Enemy enemy) {
				return position == enemy.getPosition();
			});
			
			VectorUtils::removeIf(_bricks, [position] (Brick& brick) {
				return brick.destructible() && position == brick.position();
			});
			
			if (_player->position() == position) {
				_player->die();
				playerRespawn.start();
			}
		}
	}
	
	void TileMap::updateExplosions() {
		for (Explosion& explosion : _explosions) {
			explosion.update();
		}
	}
	
	void TileMap::clearExplosions() {
		_explosions.remove_if([] (Explosion explosion) {
			return explosion.done();
		});
	}
}
