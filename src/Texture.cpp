//
//  Texture.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Texture.hpp"

#include <SDL2/SDL.h>
#include <algorithm>

namespace Bomberman {
	void DestroyTexture(SDL_Texture *texture) {
		SDL_DestroyTexture(texture);
	}
	
	Texture::Texture(SDL_Texture *texture) : texture(texture, DestroyTexture) {
		
	}
	
	void Texture::draw(std::shared_ptr<SDL_Renderer> renderer) {
		SDL_RenderCopy(renderer.get(), texture.get(), nullptr, nullptr);
	}
	
	void Texture::draw(std::shared_ptr<SDL_Renderer> renderer, int i, int j) {
		SDL_Rect pos;
		
		pos.x = i;
		pos.y = j;
		
		SDL_RenderCopy(renderer.get(), texture.get(), &pos, nullptr);
	}
}
