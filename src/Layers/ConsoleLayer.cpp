//
//  ConsoleLayer.cpp
//  Bomberman
//
//  Created on 16/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "ConsoleLayer.hpp"

#include "../Math/Rectangle.hpp"

using namespace std;

namespace Bomberman {
	const int ConsoleLayer::QUEUE_SIZE = 15;
	
	ConsoleLayer::ConsoleLayer() {
		shouldDraw(false);
	}
	
	void ConsoleLayer::update() {
		
	}
	
	void ConsoleLayer::draw() {
		background.draw();
	}
	
	void ConsoleLayer::loadGraphics(shared_ptr<SDL_Renderer> renderer) {
		this->renderer = renderer;
		fontSmall = Font("PressStart2P.ttf", 8, renderer);
	}
	
	void ConsoleLayer::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
		background = Texture::createRectangle(newSize.width, newSize.height * .2, Color(0x55, 0x55, 0x55), renderer);
	}
	
	void ConsoleLayer::setInput(string input) {
	}
	
	void ConsoleLayer::clearInput() {
	}
	
	void ConsoleLayer::recieveLog(string text, LogLevel level) {
		if (lines.size() > QUEUE_SIZE) {
			lines.pop();
		}
		
		Texture line = fontSmall.write(text);
		lines.push(line);
	}
}
