//
//  Explosion.hpp
//  Bomberman
//
//  Created on 17/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#ifndef __Explosion_hpp__
#define __Explosion_hpp__

#include "../../Core/Timer.hpp"
#include "../../Core/Math/Coordinate.hpp"

#include <memory>
#include <vector>

namespace Bomberman {
    class TileMap;
    
    class Explosion {
    public:
        Explosion(Coordinate position, int size, std::shared_ptr<TileMap> tileMap);
        ~Explosion();
        
        void update();
        
        bool done() const;
        std::vector<Coordinate> hitArea() const;

    private:
        static const int TTL;
        
        std::vector<Coordinate> _hitArea;
        Coordinate position;
        Timer timer;
        bool _done;
    };
}

#endif // __Explosion_hpp__
