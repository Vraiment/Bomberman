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
	void getEnemyTexture(const char *enemyType) {
		
	}
	
	GameLayer::~GameLayer() {
		
	}
	
	void GameLayer::draw() {
		Texture texture;
		
		background.rectangle() = camera;
		background.draw();
		
		// Draw bricks
		auto bricks = tileMap->bricks();
		for (auto brick : bricks) {
			texture = (brick.destructible()) ? destructibleBrick : this->brick;
			
			drawTile(texture, brick.position());
		}
		
		// Draw bombs
		auto bombs = tileMap->bombs();
		for (auto bomb : bombs) {
			drawTile(this->bomb, bomb.getPosition());
		}
		
		// Draw player
		auto player = tileMap->player();
		if (!player->isDead()) {
			drawTile(this->player, player->position());
		}
		
		// Draw enemies
		auto enemies = tileMap->enemies();
		texture = Texture();
		for (auto enemy : enemies) {
			if (getEnemyTexture(enemy.getType(), texture)) {
				drawTile(texture, enemy.getPosition());
			}
		}
		
		// Draw explosions
		auto explosions = tileMap->explosions();
		for (auto explosion : explosions) {
			auto hitArea = explosion.hitArea();
			
			for (auto position : hitArea) {
				if (tileMap->area().contains(position) && !tileMap->tileHasBrick(position)) {
					drawTile(this->explosion, position);
				}
			}
		}
	}
	
	void GameLayer::update() {
		tileMap->update();
	}
	
	void GameLayer::loadGraphics(shared_ptr<SDL_Renderer> renderer) {
		background = Texture("background.png", renderer);
		bomb = Texture("bomb.png", renderer);
		brick = Texture("brick.png", renderer);
		destructibleBrick = Texture("destructibleBrick.png", renderer);
		explosion = Texture("explosion.png", renderer);
		player = Texture("bomberman.png", renderer);
		
		Texture enemy;
		
		enemy = Texture("enemy1.png", renderer);
		enemies.push_back(enemy);
		enemy = Texture("enemy2.png", renderer);
		enemies.push_back(enemy);
		enemy = Texture("enemy3.png", renderer);
		enemies.push_back(enemy);
	}
	
	void GameLayer::setTileMap(shared_ptr<TileMap> tileMap) {
		this->tileMap = tileMap;
	}
	
	void GameLayer::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
		camera.width = newSize.width;
		camera.height = newSize.height;
	}
	
	void GameLayer::drawTile(Texture texture, Coordinate position) {
		position.i *= TILE_WIDTH;
		position.j *= TILE_HEIGHT;
		
		texture.position() = position;
		texture.draw();
	}
	
	bool GameLayer::getEnemyTexture(string enemyType, Texture& texture) {
		bool result = true;
		
		if (ENEMY_EASY == enemyType) {
			texture = enemies[0];
		} else if (ENEMY_MEDIUM == enemyType) {
			texture = enemies[1];
		} else if (ENEMY_HARD == enemyType) {
			texture = enemies[2];
		} else {
			result = false;
			Log::get() << "Invalid enemy type: " << enemyType << "." << LogLevel::warning;
		}
		
		return result;
	}
}
