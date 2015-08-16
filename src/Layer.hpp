//
//  Layer.hpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __Layer__hpp__
#define __Layer__hpp__

struct SDL_Renderer;

#include <memory>

namespace Bomberman {
	class Rectangle;
	
	class Layer {
	public:
		virtual ~Layer();
		
		virtual void update() = 0;
		virtual void draw() = 0;
		
		bool isZombie() const;
		
		virtual void loadGraphics(std::shared_ptr<SDL_Renderer> render) = 0;
		
		virtual void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
		
	protected:
		bool _isZombie;
	};
}

#endif //__Layer__hpp__
