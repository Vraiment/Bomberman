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
        
        life.setAlpha(Texture::OPAQUE * .50);
        for (int n = player->getLifesCount(); n < player->getMaxLifes(); ++n) {
            life.rectangle().i = n * life.rectangle().height;
            life.draw();
        }
        
        if (player->getLifesCount() == 0) {
            background.draw();
            gameOver.draw();
            continueText.draw();
        }
    }
    
    void HudLayer::update() {
        
    }
    
    void HudLayer::setPlayer(shared_ptr<Player> player) {
        this->player = player;
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
        
        Font font("PressStart2P.ttf", 75, renderer);
        font.setUnderLine();
        gameOver = font.write("GAME OVER", Color::RED);
        
        font = Font("PressStart2P.ttf", 25, renderer);
        continueText = font.write("Press any key to return...", Color::RED);
        
        background = Texture::createRectangle(1, 1, Color::BLACK, renderer);
        background.setAlpha(Texture::OPAQUE * .50);
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
