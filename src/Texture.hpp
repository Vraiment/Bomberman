//
//  Texture.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Texture__hpp__
#define __Texture__hpp__

#include <memory>

struct SDL_Texture;
struct SDL_Renderer;

namespace Bomberman {
	class Texture {
	public:
		Texture(SDL_Texture *texture);
		
		void draw(std::shared_ptr<SDL_Renderer> renderer);
		void draw(std::shared_ptr<SDL_Renderer> renderer, int i, int j);
		
	private:
		std::shared_ptr<SDL_Texture> texture;
	};
}

#endif //__Texture__hpp__
