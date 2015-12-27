//
//  GameLayer.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __GameLayer__hpp__
#define __GameLayer__hpp__

#include "../Layer.hpp"

#include <string>
#include <vector>

#include "../Texture.hpp"
#include "../Timer.hpp"

namespace Bomberman {
    class TileMap;
    
    class GameLayer : public Layer {
    public:
        GameLayer();
        
        ~GameLayer();
        
        void draw();
        void update();
        
        void loadGraphics(std::shared_ptr<SDL_Renderer> renderer);
        
        void setTileMap(std::shared_ptr<TileMap> tileMap);
        
        void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
        
    private:
        class Camera;
        
        static const int PLAYER_BLINK_TIME;
        
        bool drawPlayer;
        Texture background;
        Texture bomb;
        Texture brick;
        Texture destructibleBrick;
        std::vector<Texture> enemies;
        Texture explosion;
        Texture player;
        Texture extraBomb;
        Texture increaseRange;
        Texture remote;
        Timer blinkPlayerTimer;
        
        std::shared_ptr<TileMap> tileMap;
        
        std::shared_ptr<Camera> camera;
        
        void drawBackground();
        void drawTile(Texture texture, Coordinate position);
        bool getEnemyTexture(std::string enemyType, Texture& texture);
    };
}

#endif //__GameLayer__hpp__
