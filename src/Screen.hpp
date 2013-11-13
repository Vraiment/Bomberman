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

namespace Bomberman {
	class Screen {
	public:
		Screen(int width, int height, std::string name);
		virtual ~Screen();
		
		virtual void draw() = 0;
		
		std::string getName() const;
		int getWidth() const;
		int getHeight() const;
		
		void setName(std::string name);
		void setWidth(int width);
		void setHeight(int height);
		
		std::shared_ptr<SDL_Renderer> renderer() const;
		
	protected:
		virtual void nameChanged(std::string prevName);
		virtual void widthChanged(int prevWidth);
		virtual void heightChanged(int prevHeight);
		
	private:
		void initialize();
		
		std::string name;
		std::shared_ptr<SDL_Window> window;
		std::shared_ptr<SDL_Renderer> _renderer;
		int width, height;
	};
}

#endif //__Screen__hpp__
