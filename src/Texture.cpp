//
//  Texture.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Texture.hpp"

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

using namespace std;

namespace Bomberman {
	void DestroyTexture(SDL_Texture *texture) {
		SDL_DestroyTexture(texture);
	}
	
	Texture::Texture() : texture(nullptr), renderer(nullptr), _loaded(false) {
		
	}
	
	Texture::Texture(string fileName, std::shared_ptr<SDL_Renderer> renderer) : texture(nullptr), renderer(renderer), _loaded(false), name(fileName) {
		string fullName = "textures";
		fullName += dirSeparator;
		fullName += fileName;
		
		SDL_Texture *t = IMG_LoadTexture(renderer.get(), fullName.c_str());
		
		if (t != nullptr) {
			texture.reset(t, DestroyTexture);
			_loaded = true;
		} else {
			Logger::log("Could not load texture \"" + fileName + "\".", LogLevel::warning);
		}
	}
	
	bool Texture::loaded() const {
		return _loaded;
	}
	
	void Texture::draw(int i, int j) {
		if (!_loaded) {
			Logger::log("Trying to draw not loaded texture \"" + name + "\".", LogLevel::warning);
			
			return;
		}
		
		SDL_Rect dst;
		
		dst.x = i;
		dst.y = j;
		
		SDL_QueryTexture(texture.get(), nullptr, nullptr, &dst.w, &dst.h);
		
		SDL_RenderCopy(renderer.get(), texture.get(), nullptr, &dst);
	}
	
	string Texture::getName() const {
		return name;
	}
}
