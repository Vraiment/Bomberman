//
//  Screen.hpp
//  Bomberman
//
//  Created on 02/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Screen__hpp__
#define __Screen__hpp__

#include <memory>
#include <string>
#include <SDL2/SDL.h>

#include "Rectangle.hpp"

namespace Bomberman {
	class Screen {
	public:
		Screen(int width, int height, std::string name);
		virtual ~Screen();
		
		virtual void draw() = 0;
		
		std::string name() const;
		int width() const;
		int height() const;
		Rectangle rectangle() const;
		
		void setName(std::string name);
		void setWidth(int width);
		void setHeight(int height);
		void setSize(int width, int height);
		
		std::shared_ptr<SDL_Renderer> renderer() const;
		
	protected:
		virtual void nameChanged(std::string prevName);
		virtual void sizeChanged(Rectangle previousSize);
		
	private:
		void refereshSize(Rectangle previousSize);
		
		std::string _name;
		std::shared_ptr<SDL_Window> window;
		std::shared_ptr<SDL_Renderer> _renderer;
		Rectangle _rectangle;
	};
}

#endif //__Screen__hpp__
