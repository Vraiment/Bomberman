//
//  Color.hpp
//  Bomberman
//
//  Created on 16/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __Color__hpp__
#define __Color__hpp__

#include <cinttypes>

struct SDL_Color;

namespace Bomberman {
	class Color {
	public:
		Color(uint8_t value = 0);
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = OPAQUE);
		
		uint8_t getRed() const;
		uint8_t getGreen() const;
		uint8_t getBlue() const;
		uint8_t getAlpha() const;
		
		void setRed(uint8_t r);
		void setGreen(uint8_t g);
		void setBlue(uint8_t b);
		void setAlpha(uint8_t a);
		
		SDL_Color sdlColor() const;
		
		static const uint8_t OPAQUE;
		static const uint8_t TRANSPARENT;
		
		static const Color WHITE;
		static const Color BLACK;
		
		static const Color RED;
		static const Color GREEN;
		static const Color BLUE;
		
		static const Color CYAN;
		static const Color MAGENTA;
		static const Color YELLOW;
		
	private:
		uint8_t r, g, b, a;
	};
}

#endif //__Color__hpp__
