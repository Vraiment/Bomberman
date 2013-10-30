//
//  TileMapBuilder.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __TileMapBuilder__hpp__
#define __TileMapBuilder__hpp__

namespace Bomberman {
	class Texture;
	
	class TileMapBuilder {
	public:
		int getMapWidth() const;
		int getMapHeight() const;
		
		Texture getTexture(int column, int row) const;
		
	private:
		int mapWidth, mapHeight;
	};
}

#endif //__TileMapBuilder__hpp__
