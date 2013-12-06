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
#include <string>

#include "Rectangle.hpp"

struct SDL_Renderer;
struct SDL_Texture;

namespace Bomberman {
	class Texture {
	public:
		Texture();
		Texture(std::string fileName, std::shared_ptr<SDL_Renderer> renderer);
		
		void draw();
		
		std::string name() const;
		Coordinate& position();
		Rectangle& rectangle();
		void resetSize();
		
	private:
		bool _loaded;
		std::shared_ptr<SDL_Renderer> renderer;
		std::shared_ptr<SDL_Texture> texture;
		std::string _name;
		Rectangle _rectangle;
	};
}

#endif //__Texture__hpp__
