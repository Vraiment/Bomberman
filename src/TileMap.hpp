//
//  TileMap.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __TileMap__hpp__
#define __TileMap__hpp__

#include "ITileMapBuilder.hpp"

#include <vector>

struct SDL_Renderer;

namespace Bomberman {
	class Texture;
	
	class TileMap {
	public:
		TileMap(ITileMapBuilder *builder);
		~TileMap();
		
		int getWidth() const;
		int getHeight() const;
		
		void draw(SDL_Renderer *renderer);
		
	private:
		int width, height, total;
		std::vector<Texture> tiles;
	};
}

#endif //__TileMap__hpp__
