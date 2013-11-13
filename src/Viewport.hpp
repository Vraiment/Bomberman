//
//  Viewport.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Viewport__hpp__
#define __Viewport__hpp__

#include "Screen.hpp"
#include "Coordinate.hpp"
#include <vector>

namespace Bomberman {
	class TileMap;
	
	class Viewport : public Screen {
	public:
		Viewport(int width, int height, std::string name);
		
		void draw();
		
		void loadTileMap(const TileMap& tileMap);
		
		Coordinate& origin();
		
	private:
		Coordinate _origin;
		std::vector<Coordinate> bricks;
		std::vector<Coordinate> destrutibleBricks;
	};
}

#endif //__Viewport__hpp__
