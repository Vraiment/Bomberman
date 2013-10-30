//
//  Viewport.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Viewport__hpp__
#define __Viewport__hpp__

struct SDL_Renderer;

namespace Bomberman {
	class Viewport {
	public:
		int getWidth() const;
		int getHeight() const;
		
		void setWidth(int width);
		void setHeight(int height);
		
		void draw(SDL_Renderer *renderer);
		
	private:
		int width, height;
		
	};
}

#endif //__Viewport__hpp__
