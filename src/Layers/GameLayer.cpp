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
#include "../Elements/Item.hpp"
#include "../Elements/Player.hpp"
#include "../Map/TileMap.hpp"
#include "../Utils/Exception.hpp"
#include "../Log/Log.hpp"
#include "../Log/LogLevel.hpp"

using namespace std;
using namespace Bomberman::Constants;

namespace Bomberman {
    const int GameLayer::PLAYER_BLINK_TIME = 125;
    
    class GameLayer::Camera {
    public:
        void setScreenSize(Rectangle size) {
            // Camera size in tiles
            cameraWidth = size.width / TILE_WIDTH;
            cameraHeight = size.height / TILE_HEIGHT;
        }
        
        // Input position is in tile coordinates
        // Output position is in screen coordinates
        Coordinate getScreenPosition(Coordinate position) const {
            position -= static_cast<Coordinate>(tileMapOffset);
            
            position.i *= TILE_WIDTH;
            position.j *= TILE_HEIGHT;
            
            return position;
        }
        
        // Position is in tile coordinates
        bool insideCamera(Coordinate position) const {
            //return rectangle.contains(position + rectangle);
            return true;
        }
        
        void update(Coordinate newPlayerPos, Rectangle tileMapArea) {
            if (firstUpdate) {
                // Center the player in the camera, taking into account the borders
                tileMapOffset = Rectangle::ZERO;
                Rectangle cameraArea = this->cameraArea();
                
                tileMapOffset.i = newPlayerPos.i - cameraArea.widthCenter();
                if (tileMapOffset.i < (tileMapArea.left() - LEFT_BORDER)) {
                    tileMapOffset.i = -LEFT_BORDER;
                } else if (tileMapOffset.i > (tileMapArea.right() - cameraArea.width + RIGHT_BORDER)) {
                    tileMapOffset.i = tileMapArea.width - cameraArea.width + RIGHT_BORDER;
                }
                
                tileMapOffset.j = newPlayerPos.j - cameraArea.heightCenter();
                if (tileMapOffset.j < (tileMapArea.top() - TOP_BORDER)) {
                    tileMapOffset.j = -TOP_BORDER;
                } else if (tileMapOffset.j > (tileMapArea.bottom() - cameraArea.height + BOTTOM_BORDER)) {
                    tileMapOffset.j = tileMapArea.height - cameraArea.height + BOTTOM_BORDER;
                }
                
                previousPlayerPos = newPlayerPos;
                firstUpdate = false;
            } else if (previousPlayerPos != newPlayerPos) {
                Rectangle cameraArea = this->cameraArea();
                Coordinate direction = (newPlayerPos - previousPlayerPos).canonize();
                
                if (cameraArea.widthCenter() == previousPlayerPos.i) {
                    // The player was in the horizontal center.
                    // Move the offset if its moving horizontally and if
                    // there is still space to move
                    if (direction.i > 0 && tileMapOffset.i < (tileMapArea.width - cameraWidth + RIGHT_BORDER)) {
                        ++tileMapOffset.i;
                    } else if (direction.i < 0 && tileMapOffset.i > (tileMapArea.i - LEFT_BORDER)) {
                        --tileMapOffset.i;
                    }
                }
                
                if (cameraArea.heightCenter() == previousPlayerPos.j) {
                    // The player was in the vertical center
                    // Move the offset if its moving vertically
                    if (direction.j > 0 && tileMapOffset.j < (tileMapArea.height - cameraHeight + BOTTOM_BORDER)) {
                        ++tileMapOffset.j;
                    } else if (direction.j < 0 && tileMapOffset.j > (tileMapArea.j - TOP_BORDER)) {
                        --tileMapOffset.j;
                    }
                }
                
                previousPlayerPos = newPlayerPos;
            }
        }
        
    private:
        const int RIGHT_BORDER = 1;
        const int LEFT_BORDER = 1;
        const int TOP_BORDER = 2;
        const int BOTTOM_BORDER = 1;
        
        bool firstUpdate = true;
        
        // The position of the player since last update.
        Coordinate previousPlayerPos;
        
        // Offset from tile map's [0,0] in tiles.
        Coordinate tileMapOffset;
        
        // Size of the camera in tiles.
        int cameraWidth, cameraHeight;
        
        // The rectangle of the camera
        Rectangle cameraArea() const {
            return Rectangle(tileMapOffset.i, tileMapOffset.j, cameraWidth, cameraHeight);
        }
    };
    
    GameLayer::GameLayer() : camera(new Camera()), drawPlayer(true) {
        
    }
    
    GameLayer::~GameLayer() {
        
    }
    
    void GameLayer::draw() {
        Texture texture;
        
        background.rectangle() = camera->getScreenPosition(Coordinate::ZERO);
        background.draw();
        
        // Draw Items
        auto items = tileMap->items();
        for (auto item : items) {
            if (Item::INCREASE_RANGE == item) {
                texture = increaseRange;
            } else if (Item::EXTRA_BOMB == item) {
                texture = extraBomb;
            } else if (Item::REMOTE == item) {
                texture = remote;
            } else {
                Log::get() << "No valid texture for item with id: " << item.id() << LogLevel::warning;
                continue;
            }
            
            drawTile(texture, item.getPosition());
        }
        
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
        if (!player->isDead() && drawPlayer) {
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
        camera->update(tileMap->player()->position(), tileMap->area());
        
        // Player blinking stuff
        if (tileMap->player()->isInvincible()) {
            if (!blinkPlayerTimer.isCounting()) {
                blinkPlayerTimer.start();
            } else if (blinkPlayerTimer.getTime() >= PLAYER_BLINK_TIME) {
                blinkPlayerTimer.restart();
                drawPlayer = !drawPlayer;
            }
        } else {
            drawPlayer = true;
        }
    }
    
    void GameLayer::load(shared_ptr<SDL_Renderer> renderer) {
        background = Texture("background.png", renderer);
        bomb = Texture("bomb.png", renderer);
        brick = Texture("brick.png", renderer);
        destructibleBrick = Texture("destructibleBrick.png", renderer);
        explosion = Texture("explosion.png", renderer);
        player = Texture("bomberman.png", renderer);
        extraBomb = Texture("extraBomb.png", renderer);
        increaseRange = Texture("increaseRange.png", renderer);
        remote = Texture("remote.png", renderer);
        
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
        background.rectangle().width = tileMap->area().width * TILE_WIDTH;
        background.rectangle().height = tileMap->area().height * TILE_HEIGHT;
    }
    
    void GameLayer::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
        camera->setScreenSize(newSize);
    }
    
    void GameLayer::drawTile(Texture texture, Coordinate position) {
        if (camera->insideCamera(position)) {
            texture.position() = camera->getScreenPosition(position);
            texture.draw();
        }
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
