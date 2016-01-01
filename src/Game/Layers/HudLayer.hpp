//
//  HudLayer.hpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __HudLayer__hpp__
#define __HudLayer__hpp__

#include "../../Core/Drawable.hpp"
#include "../../Core/Texture.hpp"
#include "../../Core/Updatable.hpp"

namespace Bomberman {
    class Player;
    class TileMap;
    
    class HudLayer : public Drawable, public Updatable {
    public:
        void draw();
        void update();
        
        void load(std::shared_ptr<SDL_Renderer> renderer);
        
        void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
        
        void setPlayer(std::shared_ptr<Player> player);
        void setTileMap(std::shared_ptr<TileMap> tileMap);
        
    private:
        Texture hud;
        Texture life;
        Texture extraBomb, remote;
        Texture background;
        Texture gameOver, continueText;
        Texture digits[10];
        std::shared_ptr<TileMap> tileMap;
        std::shared_ptr<Player> player;
        
        void drawBombCount(Rectangle area);
    };
}

#endif //__HudLayer__hpp__
