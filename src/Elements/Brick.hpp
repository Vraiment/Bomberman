//
//  Brick.hpp
//  Bomberman
//
//  Created on 11/14/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Brick__hpp__
#define __Brick__hpp__

#include "../Math/Coordinate.hpp"

namespace Bomberman {
    class Brick {
    public:
        Brick(Coordinate position, bool destructible = false);
        
        bool destructible() const;
        Coordinate position() const;
        
    private:
        bool _destructible;
        Coordinate _position;
    };
}

#endif //__Brick__hpp__
