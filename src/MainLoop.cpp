//
//  MainLoop.cpp
//  Bomberman
//
//  Created on 02/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "MainLoop.hpp"

#include <SDL2/SDL.h>

#include "CommandQueue.hpp"
#include "EventListener.hpp"
#include "Log/Log.hpp"
#include "Log/LogLevel.hpp"
#include "Screen.hpp"

using namespace std;

namespace Bomberman {
	MainLoop::MainLoop() : _commandQueue(new CommandQueue()) {
		
	}
	
	MainLoop::~MainLoop() {
		
	}
	
	shared_ptr<CommandQueue> MainLoop::commandQueue() {
		return _commandQueue;
	}
	
	void MainLoop::run() {
		if (screens.empty()) {
			Log::get() << "Main loop is empty." << LogLevel::error;
			return;
		}
		
		SDL_Event event;
		bool quit = false;
		
		while (!quit) {
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
				
				for (auto it = eventListeners.begin(); it != eventListeners.end(); ++it) {
					(*it)->listenEvent(event);
				}
			}
			
			for (auto it = screens.begin(); it != screens.end(); ++it) {
				SDL_RenderClear((*it)->renderer().get());
				(*it)->draw();
				SDL_RenderPresent((*it)->renderer().get());
			}
			
			_commandQueue->update();
			
			for (auto it = screens.begin(); it != screens.end(); ++it) {
				(*it)->update();
			}
		}
	}
	
	void MainLoop::addScreen(shared_ptr<Screen> screen) {
		if (hasScreen(screen)) {
			Log::get() << "Trying to insert existing screen." << LogLevel::error;
			return;
		}
		
		Log::get() << "Inserting screen." << LogLevel::info;
		screens.push_back(screen);
	}
	
	void MainLoop::removeScreen(shared_ptr<Screen> screen) {
		if (!hasScreen(screen)) {
			Log::get() << "Trying unexisting screen." << LogLevel::error;
			return;
		}
		
		Log::get() << "Removing screen." << LogLevel::info;
		screens.remove(screen);
	}
	
	void MainLoop::addEventListener(shared_ptr<EventListener> eventListener) {
		if (hasEventListener(eventListener)) {
			Log::get() << "Trying to insert existing event listener." << LogLevel::error;
			return;
		}
		
		Log::get() << "Inserting event listener." << LogLevel::info;
		eventListeners.push_back(eventListener);
	}
	
	
	
	bool MainLoop::hasScreen(shared_ptr<Screen> screen) {
		for (auto it = screens.begin(); it != screens.end(); ++it) {
			if (*it == screen) {
				return true;
			}
		}
		
		return false;
	}
	
	bool MainLoop::hasEventListener(shared_ptr<EventListener> eventListener) {
		for (auto it = eventListeners.begin(); it != eventListeners.end(); ++it) {
			if (*it == eventListener) {
				return true;
			}
		}
		
		return false;
	}
}
