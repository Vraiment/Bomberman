//
//  Viewport.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Viewport.hpp"

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

namespace Bomberman {
	const Coordinate Viewport::tileSize = Coordinate(40, 40);
	
	Viewport::Viewport(int width, int height, string name) : Screen(width, height, name) {
		hud = Texture("hud.png", renderer());
		
		background = Texture("background.png", renderer());
		bomb = Texture("bomb.png", renderer());
		brick = Texture("brick.png", renderer());
		destructibleBrick = Texture("destructibleBrick.png", renderer());
		explosion = Texture("explosion.png", renderer());
		player = Texture("bomberman.png", renderer());
		
		Texture enemy;
		
		enemy = Texture("enemy1.png", renderer());
		enemies.push_back(enemy);
		enemy = Texture("enemy2.png", renderer());
		enemies.push_back(enemy);
		enemy = Texture("enemy3.png", renderer());
		enemies.push_back(enemy);
		
		sizeChanged(Rectangle());
		
		// HUD height is one tile
		hud.rectangle().height = tileSize.j;
	}
	
	Viewport::~Viewport() {
		
	}
	
	void Viewport::sizeChanged(Rectangle previousSize) {
		if (previousSize.width != width()) {
			center.i = width() / 2;
			
			hud.rectangle().width = width();
		}
		
		if (previousSize.height != height()) {
			center.j = height() / 2;
		}
	}
	
	void Viewport::draw() {
		if (!shouldDraw()) {
			return;
		}
		
		drawGame();
		drawHud();
	}
	
	void Viewport::drawHud() {
		hud.draw();
	}
	
	void Viewport::drawGame() {
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
			
			drawTile(texture, it->position());
		}
		
		// Draw bombs
		auto bombs = tileMap->bombs();
		for (auto bomb = bombs.begin(); bomb != bombs.end(); ++bomb) {
			if (!drawArea.contains(bomb->getPosition())) {
				continue;
			}
			
			drawTile(this->bomb, bomb->getPosition());
		}
		
		// Draw player
		if (!tileMap->player()->isDead()) {
			drawTile(player, tileMap->player()->position());
		}
		
		// Draw enemies
		list<Enemy> enemies = tileMap->enemies();
		for (auto& enemy : enemies) {
			int textureNumber = -1;
			if (enemy.getRange() == 3) {
				textureNumber = 0;
			} else if (enemy.getRange() == 5) {
				textureNumber = 1;
			} else if (enemy.getRange() == 6) {
				textureNumber = 2;
			} else {
				Log::get() << "Invalid enemy range: " << enemy.getRange() << "." << LogLevel::warning;
			}
			
			drawTile(this->enemies[textureNumber], enemy.getPosition());
		}
		
		// Draw explosions
		auto explosions = tileMap->explosions();
		for (auto explosion = explosions.begin(); explosion != explosions.end(); ++explosion) {
			auto hitArea = explosion->hitArea();
			
			for (auto pos = hitArea.begin(); pos != hitArea.end(); ++pos) {
				if (!tileMap->area().contains(*pos) || tileMap->tileHasBrick(*pos)) {
					continue;
				}
				
				drawTile(this->explosion, *pos);
			}
		}
	}
	
	void Viewport::drawTile(Texture texture, Coordinate position) {
		texture.position() = (position * tileSize) - offset;
		texture.draw();
	}
	
	void Viewport::update() {
		tileMap->update();
		
		// Camera stuff
		auto player = tileMap->player();
		if (player->position() == lastPlayerPos) {
			return;
		}
		
		Coordinate delta = player->position() - lastPlayerPos;
		Rectangle view = buildView();
		
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
		
		// Set the camera
		auto player = this->tileMap->player();
		Rectangle view = buildView();
		
		if (player->position().i == view.left()) {
			offset.i -= tileSize.i;
		} else if (player->position().i == view.right()) {
			offset.i += tileSize.i;
		}
		
		if (player->position().j == view.top()) {
			offset.j -= tileSize.j;
		} else if (player->position().j == view.right()) {
			offset.j += tileSize.j;
		}
	}
	
	bool Viewport::shouldDraw() {
		return
			tileMap &&
			tileMap->width() > 1 &&
			tileMap->height() > 1
		;
	}
	
	Rectangle Viewport::buildView() {
		return Rectangle(offset.i / tileSize.i, offset.j / tileSize.j, width() / tileSize.i, height() / tileSize.j);
	}
}
