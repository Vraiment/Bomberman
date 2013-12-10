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
	class CommandQueue;
	
	class MainLoop {
	public:
		MainLoop();
		~MainLoop();
		
		void run();
		
		void addScreen(std::shared_ptr<Screen> screen);
		
		void removeScreen(std::shared_ptr<Screen> screen);
		
		void addEventListener(std::shared_ptr<EventListener> eventListener);
		
		void removeEventListener(std::shared_ptr<EventListener> eventListener);
		
		std::shared_ptr<CommandQueue> commandQueue();
		
	private:
		bool hasScreen(std::shared_ptr<Screen> screen);
		bool hasEventListener(std::shared_ptr<EventListener> eventListener);
		
		std::list<std::shared_ptr<Screen>> screens;
		std::list<std::shared_ptr<EventListener>> eventListeners;
		std::shared_ptr<CommandQueue> _commandQueue;
	};
}

#endif //__MainLoop__hpp__
