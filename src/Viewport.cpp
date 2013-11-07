//
//  Viewport.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Viewport.hpp"

using namespace std;

namespace Bomberman {
	Viewport::Viewport(int width, int height, string name) : Screen(width, height, name) {
		widthChanged(0);
		heightChanged(0);
	}
	
	void Viewport::draw(shared_ptr<SDL_Renderer> renderer) {
		throw NotImplementedException();
	}
	
	void Viewport::widthChanged(int prevWidth) {
		count.i = getWidth() / tileMap.getTexturesWidth();
	}
	
	void Viewport::heightChanged(int prevHeight) {
		count.j = getHeight() / tileMap.getHeight();
	}
	
	Coordinate& Viewport::origin() {
		return _origin;
	}
}
