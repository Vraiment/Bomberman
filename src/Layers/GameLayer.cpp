//
//  GameLayer.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "GameLayer.hpp"

#include <SDL2/SDL.h>

#include "../Constants.hpp"
#include "../Elements/Bomb.hpp"
#include "../Elements/Brick.hpp"
#include "../Elements/Enemy.hpp"
#include "../Elements/Explosion.hpp"
#include "../Elements/Player.hpp"
#include "../Map/TileMap.hpp"
#include "../Utils/Exception.hpp"
#include "../Log/Log.hpp"
#include "../Log/LogLevel.hpp"

using namespace std;
using namespace Bomberman::Constants;

namespace Bomberman {
	GameLayer::~GameLayer() {
		
	}
	
	void GameLayer::draw() {
		
	}
	
	void GameLayer::update() {
		
	}
	
	void GameLayer::loadGraphics(shared_ptr<SDL_Renderer> renderer) {
		
	}
}
