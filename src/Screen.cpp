//
//  Screen.cpp
//  Bomberman
//
//  Created on 06/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Screen.hpp"

using namespace std;

namespace Bomberman {
	Screen::Screen(int width, int height, string name) : name(name), width(width), height(height) {
		initialize();
	}
	
	void Screen::initialize() {
		SDL_Window *w = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		
		if (w == nullptr) {
			Logger::log("Could not initialize window: \"" + name + "\": " + SDL_GetError() + ".", LogLevel::fatal);
		}
		
		window.reset(w, [](SDL_Window *w) {
			SDL_DestroyWindow(w);
		});
		
		SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
		
		if (r == nullptr) {
			Logger::log("Could not initialize renderer for window: \"" + name + "\": " + SDL_GetError() + ".", LogLevel::fatal);
		}
		
		_renderer.reset(r, [](SDL_Renderer *r) {
			SDL_DestroyRenderer(r);
		});
	}
	
	Screen::~Screen() {
		
	}
	
	string Screen::getName() const {
		return name;
	}
	
	int Screen::getWidth() const {
		return width;
	}
	
	int Screen::getHeight() const {
		return height;
	}
	
	void Screen::setName(string name) {
		if (name != this->name) {
			string prev = this->name;
			this->name = name;
			
			SDL_SetWindowTitle(window.get(), name.c_str());
			nameChanged(prev);
		}
	}
	
	void Screen::nameChanged(string prevName) {
		
	}
	
	void Screen::setWidth(int width) {
		if (width != this->width) {
			int prev = this->width;
			this->width = width;
			
			SDL_SetWindowSize(window.get(), width, height);
			widthChanged(prev);
		}
	}
	
	void Screen::widthChanged(int prevWidth) {
		
	}
	
	void Screen::setHeight(int height) {
		if (height != this->height) {
			int prev = this->height;
			this->height = height;
			
			SDL_SetWindowSize(window.get(), width, height);
			heightChanged(prev);
		}
	}
	
	void Screen::heightChanged(int prevHeight) {
		
	}
}
