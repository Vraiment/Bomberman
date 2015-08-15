//
//  HudLayer.cpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "HudLayer.hpp"

#include "Constants.hpp"
#include "GameLayer.hpp"
#include "../Math/Rectangle.hpp"

using namespace Bomberman::Constants;
using namespace std;

namespace Bomberman {
	void HudLayer::draw() {
		hud.draw();
	}
	
	void HudLayer::update() {
		
	}
	
	void HudLayer::loadGraphics(shared_ptr<SDL_Renderer> renderer) {
		hud = Texture("hud.png", renderer);
		
		// HUD height is one tile
		hud.rectangle().height = TILE_HEIGHT;
	}
	
	void HudLayer::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
		hud.rectangle().width = newSize.width;
	}
}
