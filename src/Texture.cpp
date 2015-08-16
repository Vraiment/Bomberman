//
//  Texture.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Texture.hpp"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "Constants.hpp"
#include "Log/Log.hpp"
#include "Log/LogLevel.hpp"
#include "Utils/OperatingSystem.hpp"

using namespace std;
using namespace Bomberman::Constants;

namespace Bomberman {
	Texture::Texture() : texture(nullptr), renderer(nullptr), _loaded(false), _rectangle() {
		
	}
	
	Texture::Texture(string fileName, std::shared_ptr<SDL_Renderer> renderer) : texture(nullptr), renderer(renderer), _loaded(false), _name(fileName) {
		string fullName = getPath({ DIR_TEXTURES }, _name);
		
		SDL_Texture *t = IMG_LoadTexture(renderer.get(), fullName.c_str());
		
		loadTexture(t);
	}
	
	Texture::Texture(SDL_Texture *t, string name, shared_ptr<SDL_Renderer> renderer) : texture(nullptr), renderer(renderer), _loaded(false), _name(name) {
		loadTexture(t);
	}
	
	void Texture::draw() {
		if (!_loaded) {
			Log::get() << "Trying to draw not loaded texture \"" << _name << "\"." << LogLevel::warning;
			
			return;
		}
		
		SDL_Rect dst;
		
		dst.x = _rectangle.i;
		dst.y = _rectangle.j;
		dst.w = _rectangle.width;
		dst.h = _rectangle.height;
		
		SDL_RenderCopy(renderer.get(), texture.get(), nullptr, &dst);
	}
	
	string Texture::name() const {
		return _name;
	}
	
	Coordinate& Texture::position() {
		return _rectangle;
	}
	
	Rectangle& Texture::rectangle() {
		return _rectangle;
	}
	
	void Texture::resetSize() {
		SDL_QueryTexture(texture.get(), nullptr, nullptr, &_rectangle.width, &_rectangle.height);
	}
	
	void Texture::loadTexture(SDL_Texture *t) {
		if (t != nullptr) {
			texture.reset(t, SDL_DestroyTexture);
			resetSize();
			
			_loaded = true;
		} else {
			Log::get() << "Could not load texture \"" << _name << "\"." << LogLevel::warning;
		}
	}
}
