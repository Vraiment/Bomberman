//
//  Player.hpp
//  Bomberman
//
//  Created on 12/6/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Player__hpp__
#define __Player__hpp__

#include "../../Core/Timer.hpp"
#include "../../Core/Math/Coordinate.hpp"

namespace Bomberman {
    class Item;
    
    class Player {
    public:
        Player();
        Player(int lifes);
        
        Coordinate& position();
        
        void update();
        
        void addItem(Item item);
        void setInvincibility(bool invincible);
        void setRemote(bool remote);
        
        int getExplosionSize() const;
        int maxBombs() const;
        
        bool isDead() const;
        bool isInvincible() const;
        bool hasRemote() const;
        int getLifesCount() const;
        void die();
        void respawn();
        
    private:
        static const int invincibleTime;
        static const int defaultLifeCount;
        
        bool _isInvincible;
        bool _hasRemote;
        Coordinate _position;
        Timer invincible;
        int explosionSize;
        int _maxBombs;
        bool dead;
        int lifes;
    };
}

#endif //__Player__hpp__
