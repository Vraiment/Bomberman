//
//  Viewport.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Viewport__hpp__
#define __Viewport__hpp__

#include "../Screen.hpp"

#include <string>

#include "../Texture.hpp"

struct SDL_Renderer;

namespace Bomberman {
	class TileMap;
	
	class Viewport : public Screen {
	public:
		Viewport(int width, int height, std::string name);
		~Viewport();
		
		void draw();
		void update();
		
		void loadTileMap(std::shared_ptr<TileMap> tileMap);
		
	protected:
		void sizeChanged(Rectangle previousSize);
		
	private:
		bool shouldDraw();
		Rectangle buildView();
		
		static const Coordinate tileSize;
		
		Texture background;
		Texture bomb;
		Texture brick;
		Texture destructibleBrick;
		Texture explosion;
		Texture player;
		std::shared_ptr<TileMap> tileMap;
		
		Coordinate offset; // In pixels
		Coordinate center; // In pixels
		Coordinate lastPlayerPos; // In tiles
		
		void drawHud();
		void drawGame();
	};
}

#endif //__Viewport__hpp__
