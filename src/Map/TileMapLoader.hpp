//
//  TileMapLoader.hpp
//  Bomberman
//
//  Created on 09/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __TileMapLoader__hpp__
#define __TileMapLoader__hpp__

#include <string>
#include <tinyxml2/tinyxml2.h>
#include <vector>

#include "../Elements/Player.hpp"

namespace Bomberman {
	class Brick;
	class TileMap;
	
	class TileMapLoader {
	public:
		~TileMapLoader();
		
		std::shared_ptr<TileMap> load(std::string fileName);
		
	private:
		void reset();
		
		void loadDimension(tinyxml2::XMLElement *root);
		void loadName(tinyxml2::XMLElement *name);
		void loadPlayer(tinyxml2::XMLElement *player);
		void loadBricks(tinyxml2::XMLElement *bricks);
		
		void addBrick(int number, Brick brick);
		
		std::string fileName;
		tinyxml2::XMLDocument document;
		bool error;
		std::shared_ptr<TileMap> tileMap;
	};
}

#endif //__TileMapLoader__hpp__
