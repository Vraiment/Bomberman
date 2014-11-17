//
//  Viewport.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Viewport.hpp"

#include "../Elements/Player.hpp"
#include "../Elements/Brick.hpp"
#include "../Map/TileMap.hpp"
#include "../Utils/Exception.hpp"
#include "../Log/Log.hpp"
#include "../Log/LogLevel.hpp"

using namespace std;

namespace Bomberman {
	const Coordinate Viewport::tileSize = Coordinate(40, 40);
	
	Viewport::Viewport(int width, int height, string name) : Screen(width, height, name) {
		background = Texture("background.png", renderer());
		brick = Texture("brick.png", renderer());
		destructibleBrick = Texture("destructibleBrick.png", renderer());
		player = Texture("bomberman.png", renderer());
		
		sizeChanged(Rectangle());
	}
	
	Viewport::~Viewport() {
		
	}
	
	void Viewport::sizeChanged(Rectangle previousSize) {
		if (previousSize.width != width()) {
			center.i = width() / 2;
		}
		
		if (previousSize.height != height()) {
			center.j = height() / 2;
		}
	}
	
	void Viewport::draw() {
		if (!shouldDraw()) {
			return;
		}
		
		// Draw background
		background.position() = -offset;
		background.draw();
		
		Rectangle drawArea;
		drawArea.i = offset.i / tileSize.i;
		drawArea.j = offset.j / tileSize.j;
		drawArea.width = width() / tileSize.i;
		drawArea.height = width() / tileSize.j;
		
		// Draw bricks
		auto bricks = tileMap->bricks();
		for (auto it = bricks.begin(); it != bricks.end(); ++it) {
			if (!drawArea.contains(it->position())) {
				continue;
			}
			
			auto texture = (it->destructible()) ? destructibleBrick : brick;
			
			texture.position() = (it->position() * tileSize) - offset;
			texture.draw();
		}
		
		//Draw player
		player.position() = (tileMap->player()->position() * tileSize) - offset;
		player.draw();
	}
	
	void Viewport::update() {
		tileMap->update();
		
		// Camera stuff
		auto player = tileMap->player();
		if (player->position() == lastPlayerPos) {
			return;
		}
		
		Coordinate delta = player->position() - lastPlayerPos;
		Rectangle view(offset.i / tileSize.i, offset.j / tileSize.j, width() / tileSize.i, height() / tileSize.j);
		
		bool onLeft = delta.i < 0 && player->position().i == view.left();			// Player moves left in the left corner
		bool onRight = delta.i > 0 && player->position().i == view.right();			// Player moves right in the right corner
		if (onLeft || onRight) {
			offset.i += delta.i * tileSize.i;
		}
		
		bool onTop = delta.j < 0 && player->position().j == view.top();			// Player moves up in the top corner
		bool onBottom = delta.j > 0 && player->position().j == view.bottom();	// Player moves down in the bottom tile
		if (onTop || onBottom) {
			offset.j += delta.j * tileSize.j;
		}
		
		lastPlayerPos = player->position();
	}
	
	void Viewport::loadTileMap(shared_ptr<TileMap> tileMap) {
		this->tileMap = tileMap;
		
		background.rectangle().width = tileSize.i * tileMap->width();
		background.rectangle().height = tileSize.j * tileMap->height();
	}
	
	bool Viewport::shouldDraw() {
		return
			tileMap &&
			tileMap->width() > 1 &&
			tileMap->height() > 1
		;
	}
}
