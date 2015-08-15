//
//  GameLayer.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Viewport__hpp__
#define __Viewport__hpp__

#include "../Layer.hpp"

#include <string>
#include <vector>

#include "../Texture.hpp"

namespace Bomberman {
	class TileMap;
	
	class GameLayer : public Layer {
	public:
		~GameLayer();
		
		void draw();
		void update();
		
		void loadGraphics(std::shared_ptr<SDL_Renderer> renderer);
		
	private:
		
	};
}

#endif //__Viewport__hpp__
