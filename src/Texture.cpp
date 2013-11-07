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
		SDL_Texture *t = IMG_LoadTexture(renderer.get(), fileName.c_str());
		
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
		
		SDL_Rect pos;
		
		pos.x = i;
		pos.y = j;
		
		SDL_RenderCopy(renderer.get(), texture.get(), &pos, nullptr);
	}
	
	string Texture::getName() const {
		return name;
	}
}
