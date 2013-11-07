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

namespace tinyxml2 {
	struct XMLElement;
}

namespace Bomberman {
	class TileMapBuilder {
	public:
		TileMapBuilder(std::string fileName);
		
		int getMapWidth() const;
		int getMapHeight() const;
		
		std::string getMapName() const;
		
		int getTexturesWidth() const;
		int getTexturesHeight() const;
		
		std::string getTextureName(int column, int row) const;
		
	private:
		void loadInfo(tinyxml2::XMLElement *root);
		void fillMatrix(tinyxml2::XMLElement *tiles);
		
		int textureWidth, textureHeight;
		int mapWidth, mapHeight;
		Matrix<std::string> names;
		std::string mapName;
	};
}

#endif //__TileMapBuilder__hpp__
