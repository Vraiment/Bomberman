//
//  DummyTileMapBuilder.hpp
//  Bomberman
//
//  Created on 30/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#ifndef __DummyTileMapBuilder_hpp__
#define __DummyTileMapBuilder_hpp__

#include "TileMapBuilder.hpp"

namespace Bomberman {
    class DummyTileMapBuilder : public TileMapBuilder {
    public:
        int _width = 0, _height = 0;
        struct {
            int easy = 3;
            int medium = 5;
            int hard = 6;
        } enemiesRange;
        struct {
            int easy = 1500;
            int medium = 1000;
            int hard = 750;
        } enemiesSpeed;
        std::string _name;
        std::vector<Brick> _bricks;
        std::vector<Enemy> _enemies;
        std::vector<Item> _items;
        std::shared_ptr<Player> _player;
        
        int width() const;
        
        int height() const;
        
        int enemyRange(std::string enemyType) const;
        
        int enemySpeed(std::string enemyType) const;
        
        std::string name() const;
        
        std::vector<Brick> bricks() const;
        
        std::vector<Enemy> enemies() const;
        
        std::vector<Item> items() const;
        
        std::shared_ptr<Player> player() const;
    };
}
#endif // __DummyTileMapBuilder_hpp__
