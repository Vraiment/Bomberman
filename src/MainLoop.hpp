//
//  MainLoop.hpp
//  Bomberman
//
//  Created on 02/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __MainLoop__hpp__
#define __MainLoop__hpp__

#include <list>

namespace Bomberman {
	class Screen;
	class EventListener;
	
	class MainLoop {
	public:
		void run();
		
		void addScreen(std::shared_ptr<Screen> screen);
		
		void removeScreen(std::shared_ptr<Screen> screen);
		
		void addEventListener(std::shared_ptr<EventListener> eventListener);
		
		void removeEventListener(std::shared_ptr<EventListener> eventListener);
		
	private:
		bool hasScreen(std::shared_ptr<Screen> screen);
		bool hasEventListener(std::shared_ptr<EventListener> eventListener);
		
		std::list<std::shared_ptr<Screen>> screens;
		std::list<std::shared_ptr<EventListener>> eventListeners;
	};
}

#endif //__MainLoop__hpp__
