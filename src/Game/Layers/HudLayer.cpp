//
//  HudLayer.cpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "HudLayer.hpp"

#include "../Constants.hpp"
#include "GameLayer.hpp"
#include "../../Core/Math/Rectangle.hpp"
#include "../../Core/Color.hpp"
#include "../../Core/Font.hpp"
#include "../Elements/Player.hpp"
#include "../Map/TileMap.hpp"

using namespace Bomberman::Constants;
using namespace std;

namespace Bomberman {
    void HudLayer::draw() {
        hud.draw();
        
        life.setAlpha(Texture::OPAQUE);
        for (int n = 0; n < player->getLifesCount(); ++n) {
            life.rectangle().i = n * life.rectangle().height;
            life.draw();
        }
        
        life.setAlpha(Texture::OPAQUE * .25);
        for (int n = player->getLifesCount(); n < player->getMaxLifes(); ++n) {
            life.rectangle().i = n * life.rectangle().height;
            life.draw();
        }
        
        if (player->hasRemote()) {
            remote.setAlpha(Texture::OPAQUE);
        } else {
            remote.setAlpha(Texture::OPAQUE * .25);
        }
        remote.rectangle().i = life.rectangle().right() + (life.rectangle().width);
        remote.draw();
        
        extraBomb.rectangle().i = remote.rectangle().right() + (remote.rectangle().width * 2);
        extraBomb.draw();
        Rectangle area = extraBomb.rectangle();
        area.i -= remote.rectangle().width;
        drawNumber(player->maxBombs() - tileMap->bombCount(), area);
        
        explosion.rectangle().i = extraBomb.rectangle().right() + (extraBomb.rectangle().width * 2);
        explosion.draw();
        area = explosion.rectangle();
        area.i -= extraBomb.rectangle().width;
        drawNumber(player->getExplosionSize(), area);
        
        area.i = hud.rectangle().right() - TILE_WIDTH;
        area.j = hud.rectangle().i;
        area.width = TILE_WIDTH;
        area.height = TILE_HEIGHT;
        drawNumber(tileMap->enemiesLeft(), area);
        enemiesLeft.rectangle().i = area.i - enemiesLeft.rectangle().width;
        enemiesLeft.rectangle().j = area.heightCenter() - (enemiesLeft.rectangle().height / 2);
        enemiesLeft.draw();
        
        if (player->getLifesCount() == 0) {
            background.draw();
            gameOver.draw();
            continueText.draw();
        }
    }
    
    void HudLayer::drawNumber(int numberToDraw, Rectangle area) {
        string stringToDraw = to_string(numberToDraw);
        int digitWidth = digits->rectangle().width;
        int totalSize = (int)stringToDraw.length() * digitWidth;
        int start = area.widthCenter() - (totalSize / 2);
        int j = area.heightCenter() - (digits->rectangle().height / 2);
        
        for (int n = 0; n < stringToDraw.length(); ++n) {
            char digit = stringToDraw[n];
            Texture *digitTexture = &digits[digit - '0'];
            digitTexture->rectangle().i = start + (n * digitWidth);
            digitTexture->rectangle().j = j;
            digitTexture->draw();
        }
    }
    
    void HudLayer::update() {
        
    }
    
    void HudLayer::setPlayer(shared_ptr<Player> player) {
        this->player = player;
    }
    
    void HudLayer::setTileMap(shared_ptr<TileMap> tileMap) {
        this->tileMap = tileMap;
    }
    
    void HudLayer::load(shared_ptr<SDL_Renderer> renderer) {
        hud = Texture("hud.png", renderer);
        
        // HUD height is one tile
        hud.rectangle().height = TILE_HEIGHT;
        
        life = Texture("life.png", renderer);
        life.rectangle().height = TILE_HEIGHT;
        
        extraBomb = Texture("extraBomb.png", renderer);
        extraBomb.rectangle().height = TILE_HEIGHT;
        
        remote = Texture("remote.png", renderer);
        remote.rectangle().height = TILE_HEIGHT;
        
        explosion = Texture("explosion.png", renderer);
        explosion.rectangle().height = TILE_HEIGHT;
        
        Font font("PressStart2P.ttf", 75, renderer);
        font.setUnderLine();
        gameOver = font.write("GAME OVER", Color::RED);
        
        font = Font("PressStart2P.ttf", 25, renderer);
        continueText = font.write("Press any key to return...", Color::RED);
        
        background = Texture::createRectangle(1, 1, Color::BLACK, renderer);
        background.setAlpha(Texture::OPAQUE * .50);
        
        font = Font("PressStart2P.ttf", 15, renderer);
        for (int n = 0; n < 10; ++n) {
            digits[n] = font.write(string(1, '0' + n));
        }
        
        enemiesLeft = font.write("Enemies left:");
    }
    
    void HudLayer::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
        hud.rectangle().width = newSize.width;
        
        gameOver.rectangle().i = newSize.widthCenter() - gameOver.rectangle().widthCenter();
        gameOver.rectangle().j = newSize.heightCenter() - gameOver.rectangle().heightCenter();
        
        continueText.rectangle().i = newSize.widthCenter() - continueText.rectangle().widthCenter();
        continueText.rectangle().j = gameOver.rectangle().bottom() + 10;
        
        background.rectangle() = newSize;
    }
}
