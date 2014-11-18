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

#include "../Math/Rectangle.hpp"

namespace Bomberman {
	class Bomb;
	class Brick;
	class Player;
	class TileMapBuilder;
	
	class TileMap {
	public:
		TileMap(std::shared_ptr<TileMapBuilder> builder);
		~TileMap();
		
		Rectangle area() const;
		int width() const;
		int height() const;
		std::string name() const;
		std::list<Bomb> bombs() const;
		std::vector<Brick> bricks() const;
		std::shared_ptr<Player> player() const;
		
		void update();
		
		void addBomb(Bomb bomb);
		
		bool tileHasBrick(Coordinate tile) const;
		bool tileHasBomb(Coordinate tile) const;
		
	private:
		Rectangle _area;
		std::string _name;
		std::shared_ptr<Player> _player;
		std::vector<Brick> _bricks;
		std::list<Bomb> _bombs;
	};
}

#endif //__TileMap__hpp__
