//
//  TileMap.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __TileMap__hpp__
#define __TileMap__hpp__

#include "Coordinate.hpp"
#include "Texture.hpp"
#include <vector>

namespace Bomberman {
	class TileMap {
	public:
		TileMap(std::string fileName);
		
		int getWidth() const;
		int getHeight() const;
		
		std::vector<Coordinate> spawnPoints() const;
		std::vector<Coordinate> bricks() const;
		std::vector<Coordinate> destructibleBricks() const;
		
	private:
		std::vector<Coordinate> _spawnPoints;
		std::vector<Coordinate> _bricks;
		std::vector<Coordinate> _destructibleBricks;
		int width, height;
	};
}

#endif //__TileMap__hpp__
