//
//  TileMap.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __TileMap__hpp__
#define __TileMap__hpp__

#include <string>
#include <vector>

#include "Elements/Player.hpp"
#include "Math/Rectangle.hpp"

namespace Bomberman {
	class Brick;
	
	class TileMap {
	public:
		TileMap(std::string fileName);
		~TileMap();
		
		int width() const;
		int height() const;
		
		std::string name() const;
		std::vector<Brick> bricks() const;
		Player player() const;
		
	private:
		bool loadDimension(void *);
		bool loadName(void *);
		bool loadPlayer(void *);
		void loadBricks(void *);
		
		void addBrick(Brick);
		
		Player _player;
		Rectangle rectangle;
		std::string _name, file;
		std::vector<Brick> _bricks;
	};
}

#endif //__TileMap__hpp__
