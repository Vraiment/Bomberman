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

namespace Bomberman {
	class Brick;
	
	class TileMap {
	public:
		TileMap(std::string fileName);
		~TileMap();
		
		int getWidth() const;
		int getHeight() const;
		
		std::string getName() const;
		std::vector<Brick> getBricks() const;
		
	private:
		bool loadDimension(void *);
		bool loadName(void *);
		void loadBricks(void *);
		
		void addBrick(Brick);
		
		int width, height;
		std::string name, file;
		std::vector<Brick> bricks;
	};
}

#endif //__TileMap__hpp__
