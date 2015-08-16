//
//  Color.cpp
//  Bomberman
//
//  Created on 16/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "Color.hpp"

#include <SDL2/SDL.h>

namespace Bomberman {
	Color::Color(uint8_t value) : Color(value, value, value) {
		
	}
	
	Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {
		
	}
	
	uint8_t Color::getRed() const {
		return r;
	}
	
	uint8_t Color::getGreen() const {
		return g;
	}
	
	uint8_t Color::getBlue() const {
		return b;
	}
	
	uint8_t Color::getAlpha() const {
		return a;
	}
	
	void Color::setRed(uint8_t r) {
		this->r = r;
	}
	
	void Color::setGreen(uint8_t g) {
		this->g = g;
	}
	
	void Color::setBlue(uint8_t b) {
		this->b = b;
	}
	
	void Color::setAlpha(uint8_t a) {
		this->a = a;
	}
	
	SDL_Color Color::sdlColor() const {
		SDL_Color color;
		
		color.r = r;
		color.b = b;
		color.g = g;
		color.a = a;
		
		return color;
	}
	
	const uint8_t Color::OPAQUE = 0xFF;
	const uint8_t Color::TRANSPARENT = 0x00;
	
	const Color Color::WHITE = Color(0xFF);
	const Color Color::BLACK = Color(0x00);
	
	const Color Color::RED = Color(0xFF, 0x00, 0x00);
	const Color Color::GREEN = Color(0x00, 0xFF, 0x00);
	const Color Color::BLUE = Color(0x00, 0x00, 0xFF);
	
	const Color Color::CYAN = Color(0x00, 0xFF, 0xFF);
	const Color Color::MAGENTA = Color(0xFF, 0x00, 0xFF);
	const Color Color::YELLOW = Color(0xFF, 0xFF, 0x00);
}
