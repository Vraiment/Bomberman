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
	friend class TileMapLoader;
	public:
		TileMap();
		~TileMap();
		
		int width() const;
		int height() const;
		std::string name() const;
		std::vector<Brick> bricks() const;
		Player player() const;
		
		void execute(std::string command);
		
	private:
		Player _player;
		int _width, _height;
		std::string _name;
		std::vector<Brick> _bricks;
	};
}

#endif //__TileMap__hpp__
