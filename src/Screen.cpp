//
//  Screen.cpp
//  Bomberman
//
//  Created on 06/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Screen.hpp"

#include "Log.hpp"

using namespace std;

namespace Bomberman {
	Screen::Screen(int width, int height, string name) : _name(name), _rectangle(0, 0, width, height) {
		SDL_Window *w = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _rectangle.width, _rectangle.height, SDL_WINDOW_SHOWN);
		
		if (w == nullptr) {
			Log::get() << "Could not initialize window: \"" << name << "\": " << SDL_GetError() << "." << LogLevel::error;
			return;
		}
		
		window.reset(w, [](SDL_Window *w) {
			SDL_DestroyWindow(w);
		});
		
		SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
		
		if (r == nullptr) {
			Log::get() << "Could not initialize renderer for window: \"" << name << "\": " << SDL_GetError() << "." << LogLevel::error;
			return;
		}
		
		_renderer.reset(r, [](SDL_Renderer *r) {
			SDL_DestroyRenderer(r);
		});
	}
	
	Screen::~Screen() {
		
	}
	
	string Screen::name() const {
		return _name;
	}
	
	int Screen::width() const {
		return _rectangle.width;
	}
	
	int Screen::height() const {
		return _rectangle.height;
	}
	
	Rectangle Screen::rectangle() const {
		return _rectangle;
	}
	
	void Screen::setName(string name) {
		if (name != _name) {
			string prev = _name;
			_name = name;
			
			if (window) {
				SDL_SetWindowTitle(window.get(), name.c_str());
			}
			
			nameChanged(prev);
		}
	}
	
	void Screen::setWidth(int width) {
		if (width != _rectangle.width) {
			auto prev = _rectangle;
			_rectangle.width = width;
			
			refereshSize(prev);
		}
	}
	
	void Screen::setHeight(int height) {
		if (height != _rectangle.height) {
			auto prev = _rectangle;
			_rectangle.height = height;
			
			refereshSize(prev);
		}
	}
	
	void Screen::setSize(int width, int height) {
		if (width != _rectangle.width || height != _rectangle.height) {
			auto prev = _rectangle;
			_rectangle.width = width;
			_rectangle.height = height;
			
			refereshSize(prev);
		}
	}
	
	shared_ptr<SDL_Renderer> Screen::renderer() const {
		return _renderer;
	}
	
	void Screen::nameChanged(string prevName) {
		
	}
	
	void Screen::sizeChanged(Rectangle previousSize) {
		
	}
	
	void Screen::refereshSize(Rectangle previousSize) {
		if (window) {
			SDL_SetWindowSize(window.get(), _rectangle.width, _rectangle.height);
		}
		
		sizeChanged(previousSize);
	}
}
