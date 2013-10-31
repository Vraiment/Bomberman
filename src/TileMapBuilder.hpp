//
//  TileMapBuilder.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __TileMapBuilder__hpp__
#define __TileMapBuilder__hpp__

#include "Matrix.hpp"
#include <string>

struct SDL_Renderer;

namespace Bomberman {
	class Texture;
	
	class TileMapBuilder {
	public:
		TileMapBuilder(std::string fileName, Renderer renderer);
		
		int getMapWidth() const;
		int getMapHeight() const;
		
		Texture getTexture(int column, int row) const;
		
	private:
		int mapWidth, mapHeight;
		std::string mapName;
		Matrix<Texture> tileTextures;
	};
}

#endif //__TileMapBuilder__hpp__
