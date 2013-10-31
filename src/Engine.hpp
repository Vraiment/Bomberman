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

namespace Bomberman {
	class Engine {
	public:
		Engine();
		~Engine();
		
		Renderer getRenderer() const;
		
	private:
		void setPath();
		
		std::shared_ptr<SDL_Window> window;
		Renderer renderer;
	};
}

#endif //__Engine_hpp__
