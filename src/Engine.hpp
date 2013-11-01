//
//  Engine.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Engine__hpp__
#define __Engine__hpp__

#include "Configuration.hpp"
#include "Logger.hpp"

struct SDL_Window;

namespace Bomberman {
	class Logger;
	
	class Engine {
	public:
		Engine();
		~Engine();
		
		Renderer getRenderer() const;
		Configuration getConfiguration() const;
		
		static std::shared_ptr<Logger> logger();
		
	private:
		void setPath();
		void setLoggers();
		
		static std::shared_ptr<Logger> firstLogger;
		
		std::shared_ptr<SDL_Window> window;
		Renderer renderer;
		Configuration configuration;
	};
}

#endif //__Engine_hpp__
