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
	void ConsoleLayer::update() {
		
	}
	
	void ConsoleLayer::draw() {
		
	}
	
	void ConsoleLayer::loadGraphics(shared_ptr<SDL_Renderer> renderer) {
		fontSmall = Font("PressStart2P.ttf", 8, renderer);
	}
	
	void ConsoleLayer::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
		
	}
}
