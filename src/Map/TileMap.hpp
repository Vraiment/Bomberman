//
//  TileMap.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __TileMap__hpp__
#define __TileMap__hpp__

#include <list>
#include <string>
#include <vector>

#include "../Timer.hpp"
#include "../Math/Rectangle.hpp"

namespace Bomberman {
	class Explosion;
	class Enemy;
	class Bomb;
	class Brick;
	class Player;
	class TileMapBuilder;
	
	class TileMap : public std::enable_shared_from_this<TileMap> {
	public:
		TileMap(std::shared_ptr<TileMapBuilder> builder);
		~TileMap();
		
		Rectangle area() const;
		int width() const;
		int height() const;
		std::string name() const;
		std::list<Bomb> bombs() const;
		std::vector<Brick> bricks() const;
		std::list<Enemy> enemies() const;
		std::list<Explosion> explosions() const;
		std::shared_ptr<Player> player() const;
		
		void update();
		
		void addBomb(Bomb bomb);
		int bombCount() const;
		
		bool tileHasBrick(Coordinate tile) const;
		bool tileHasBomb(Coordinate tile) const;
		
	private:
		static const int playerRespawnTime;
		
		Rectangle _area;
		std::string _name;
		std::shared_ptr<Player> _player;
		std::vector<Brick> _bricks;
		std::list<Bomb> _bombs;
		std::list<Enemy> _enemies;
		std::list<Explosion> _explosions;
		Timer playerRespawn;
		
		void updateEnemies();
		void updateBombs();
		void doDamage(std::vector<Coordinate> area);
		void updateExplosions();
		void clearExplosions();
	};
}

#endif //__TileMap__hpp__
