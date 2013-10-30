//
//  ITileMapBuilder.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __ITileMapBuilder__hpp__
#define __ITileMapBuilder__hpp__

struct SDL_Texture;

namespace Bomberman {
	class Texture;
	
	class ITileMapBuilder {
	public:
		virtual ~ITileMapBuilder() { }
		
		virtual int width() const = 0;
		virtual int height() const = 0;
		
		virtual Texture getTexture(int column, int row) const = 0;
	};
}

#endif //__ITileMapBuilder__hpp__
