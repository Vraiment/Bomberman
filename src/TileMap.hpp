//
//  TileMap.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __TileMap__hpp__
#define __TileMap__hpp__

#include "Matrix.hpp"
#include "TileMapBuilder.hpp"
#include "Texture.hpp"

namespace Bomberman {
	class TileMap {
	public:
		TileMap();
		
		void createFrom(TileMapBuilder tileMapBuilder, std::shared_ptr<SDL_Renderer> renderer);
		
		int getWidth() const;
		int getHeight() const;
		
		int getTexturesWidth() const;
		int getTexturesHeight() const;
		Texture getTileTexture(int i, int j) const;
		
	private:
		int width, height;
		Matrix<Texture> tileTextures;
	};
}

#endif //__TileMap__hpp__
