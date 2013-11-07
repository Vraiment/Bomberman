//
//  Viewport.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Viewport__hpp__
#define __Viewport__hpp__

#include "Screen.hpp"
#include "TileMap.hpp"
#include "Coordinate.hpp"

namespace Bomberman {
	class Viewport : public Screen {
	public:
		Viewport(int width, int height, std::string name);
		
		void draw(std::shared_ptr<SDL_Renderer> renderer);
		
		Coordinate& origin();
		
	protected:
		void widthChanged(int prevWidth);
		void heightChanged(int prevHeight);
		
	private:
		Coordinate count;
		Coordinate _origin;
		TileMap tileMap;
	};
}

#endif //__Viewport__hpp__
