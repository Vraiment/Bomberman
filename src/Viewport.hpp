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
#include "Coordinate.hpp"
#include "TileMap.hpp"
#include "Brick.hpp"
#include "Texture.hpp"
#include <vector>
#include <memory>

struct SDL_Renderer;

namespace Bomberman {
	class TileMap;
	
	class Viewport : public Screen {
	public:
		Viewport(int width, int height, std::string name);
		~Viewport();
		
		void draw();
		
		void loadTileMap(std::shared_ptr<TileMap> tileMap);
		
		Coordinate& origin();
		
	private:
		Coordinate transform(int x, int y);
		Coordinate transform(Coordinate coordinate);
		
		bool shouldDraw();
		void drawBackground();
		void drawBorder();
		
		static const Coordinate tileSize;
		
		Texture background;
		Texture brick;
		Texture destructibleBrick;
		std::shared_ptr<TileMap> tileMap;
		Coordinate _origin;
	};
}

#endif //__Viewport__hpp__
