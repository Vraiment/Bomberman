//
//  Engine.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Engine__hpp__
#define __Engine__hpp__

struct SDL_Window;
struct SDL_Renderer;

namespace Bomberman {
	class Engine {
	public:
		Engine();
		~Engine();
		
	private:
		SDL_Window *window = nullptr;
		SDL_Renderer *renderer = nullptr;
	};
}

#endif //__Engine_hpp__
