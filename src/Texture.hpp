//
//  Texture.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Texture__hpp__
#define __Texture__hpp__

struct SDL_Texture;
struct SDL_Renderer;

namespace Bomberman {
	class Texture {
	public:
		Texture(SDL_Texture *texture);
		Texture(const Texture& other);
		Texture(Texture&& other);
		~Texture();
		
		void draw(SDL_Renderer *renderer);
		void draw(SDL_Renderer *renderer, int i, int j);
		
		Texture& operator=(Texture other);
		
	private:
		int *references;
		SDL_Texture *texture;
		
		friend void swap(Texture& first, Texture& second);
	};
}

#endif //__Texture__hpp__
