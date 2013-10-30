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

namespace Bomberman {
	class TileMap {
	public:
		TileMap(ITileMapBuilder *builder);
		~TileMap();
		
		int getWidth() const;
		int getHeight() const;
		
	private:
		int width, height, total;
		SDL_Texture **textures;
	};
}

#endif //__TileMap__hpp__
