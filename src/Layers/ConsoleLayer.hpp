//
//  ConsoleLayer.hpp
//  Bomberman
//
//  Created on 16/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __ConsoleLayer__hpp__
#define __ConsoleLayer__hpp__

#include "../Font.hpp"
#include "../Layer.hpp"
#include "../Texture.hpp"

namespace Bomberman {
	class ConsoleLayer : public Layer {
	public:
		ConsoleLayer();
		
		void update();
		void draw();
		
		void loadGraphics(std::shared_ptr<SDL_Renderer> renderer);
		
		void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
		
	private:
		Font fontSmall;
		Texture background;
		std::shared_ptr<SDL_Renderer> renderer;
	};
}

#endif //__ConsoleLayer__hpp__
