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

using namespace std;

namespace Bomberman {
	const Coordinate Viewport::tileSize = Coordinate(40, 40);
	
	Viewport::Viewport(int width, int height, string name) : Screen(width, height, name), _origin() {
		background = Texture("background.png", renderer());
		brick = Texture("brick.png", renderer());
		destructibleBrick = Texture("destructibleBrick.png", renderer());
		player = Texture("bomberman.png", renderer());
	}
	
	Viewport::~Viewport() {
		
	}
	
	void Viewport::draw() {
		if (!shouldDraw()) {
			return;
		}
		
		updateOrigin();
		
		drawBackground();
		drawBricks();
		drawPlayer();
	}
	
	void Viewport::update() {
		tileMap->update();
	}
	
	void Viewport::loadTileMap(shared_ptr<TileMap> tileMap) {
		this->tileMap = tileMap;
		
		background.rectangle().width = tileSize.i * tileMap->width();
		background.rectangle().height = tileSize.j * tileMap->height();
	}
	
	Coordinate Viewport::transform(int i, int j) const {
		return Coordinate(_origin.i + i, _origin.j + j);
	}
	
	Coordinate Viewport::transform(Coordinate c) const {
		return transform(c.i, c.j);
	}
	
	bool Viewport::shouldDraw() {
		return
			tileMap &&
			tileMap->width() > 1 &&
			tileMap->height() > 1
		;
	}
	
	void Viewport::updateOrigin() {
		playerPos = transform(tileMap->player()->position() * tileSize);
		
		if (!rectangle().contains(playerPos)) {
			_origin += player.position() - playerPos;
		}
	}
	
	void Viewport::drawBackground() {
		background.position() = _origin;
		
		if (!rectangle().intersects(background.rectangle())) {
			return;
		}
		
		background.draw();
	}
	
	void Viewport::drawBricks() {
		auto bricks = tileMap->bricks();
		
		for (auto brick = bricks.begin(); brick != bricks.end(); ++brick) {
			Texture t = (brick->destructible()) ? this->destructibleBrick : this->brick;
			
			t.position() = _origin + (brick->position() * tileSize);
			
			t.draw();
		}
	}
	
	void Viewport::drawPlayer() {
		player.position() = playerPos;
		
		player.draw();
	}
}
