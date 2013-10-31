//
//  TileMap.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __TileMap__hpp__
#define __TileMap__hpp__

#include "TileMapBuilder.hpp"

#include <vector>

namespace Bomberman {
	class Texture;
	
	class TileMap {
	public:
		TileMap(TileMapBuilder *builder);
		~TileMap();
		
		int getWidth() const;
		int getHeight() const;
		Texture getTileTexture(int i, int j) const;
		
	private:
		int width, height;
		std::vector<Texture> tileTextures;
	};
}

#endif //__TileMap__hpp__
