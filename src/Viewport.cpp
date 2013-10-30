//
//  Viewport.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Viewport.hpp"

namespace Bomberman {
	int Viewport::getWidth() const {
		return width;
	}
	
	int Viewport::getHeight() const {
		return height;
	}
	
	void Viewport::setWidth(int width) {
		this->width = width;
	}
	
	void Viewport::setHeight(int height) {
		this->height = height;
	}
}
