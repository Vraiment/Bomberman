//
//  Font.hpp
//  Bomberman
//
//  Created on 16/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __Font__hpp__
#define __Font__hpp__

#include "Color.hpp"

#include <string>

struct SDL_Renderer;
struct _TTF_Font;

namespace Bomberman {
	class Texture;
	
	class Font {
	public:
		Font();
		Font(std::string fileName, int size, std::shared_ptr<SDL_Renderer> renderer);
		
		Texture write(std::string string, Color color = Color::WHITE);
		
		std::string name() const;
		int size() const;
		
	private:
		bool _loaded;
		std::shared_ptr<SDL_Renderer> renderer;
		std::shared_ptr<_TTF_Font> font;
		std::string _fileName;
		int _size;
		
		std::string fontId() const;
		std::string textureName(std::string string) const;
	};
}

#endif //__Font__hpp__
