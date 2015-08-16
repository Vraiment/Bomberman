//
//  Layer.cpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "Layer.hpp"

#include "Math/Rectangle.hpp"

namespace Bomberman {
	Layer::~Layer() {
		
	}
	
	bool Layer::isZombie() const {
		return _isZombie;
	}
	
	void Layer::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
		
	}
}
