//
//  Viewport.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Viewport.hpp"

#include "../Elements/Brick.hpp"
#include "../TileMap.hpp"
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
		
		drawBackground();
		drawBorder();
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
	
	Coordinate& Viewport::origin() {
		return _origin;
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
	
	void Viewport::drawBackground() {
		background.position() = origin();
		
		if (!rectangle().intersects(background.rectangle())) {
			return;
		}
		
		background.draw();
	}
	
	void Viewport::drawBorder() {
		int columns = tileMap->width() + 2;
		int rows = tileMap->height() + 1;
		int a, b;
		
		a = _origin.j - tileSize.j;
		b = _origin.j + (tileMap->height() * tileSize.j);
		
		brick.rectangle().i = _origin.i - (tileSize.i * 2);
		for (int n = 0; n < columns; ++n) {
			brick.position().i += tileSize.i;
			
			brick.position().j = a;
			brick.draw();
			
			brick.position().j = b;
			brick.draw();
		}
		
		a = _origin.i - tileSize.i;
		b = _origin.i + (tileMap->width() * tileSize.i);
		
		brick.rectangle().j = _origin.j - tileSize.j;
		for (int n = 0; n < rows; ++n) {
			brick.position().j += tileSize.j;
			
			brick.position().i = a;
			brick.draw();
			
			brick.position().i = b;
			brick.draw();
		}
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
		player.position() = transform(tileMap->player().position());
		
		player.draw();
	}
}
