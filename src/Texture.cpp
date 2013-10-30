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
	void swap(Texture& first, Texture& second) {
		using std::swap;
		
		swap(first.references, second.references);
		swap(first.texture, second.texture);
	}
	
	Texture::Texture(SDL_Texture *texture) : texture(texture), references(new int) {
		*references = 1;
	}
	
	Texture::Texture(const Texture& other) : texture(other.texture), references(other.references) {
		++(*references);
	}
	
	Texture::Texture(Texture&& other) : texture(nullptr), references(nullptr) {
		swap(*this, other);
	}
	
	Texture::~Texture() {
		if (--(*references) == 0) {
			delete references;
			SDL_DestroyTexture(texture);
		}
	}
	
	Texture& Texture::operator=(Texture other) {
		swap(*this, other);
		
		return *this;
	}
	
	void Texture::draw(SDL_Renderer *render) {
#warning TODO
	}
}
