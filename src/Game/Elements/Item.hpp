//
//  Item.hpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __Item__hpp__
#define __Item__hpp__

#include "../../Core/Math/Coordinate.hpp"

namespace Bomberman {
    class Item {
    public:
        static const Item NONE;
        static const Item EXTRA_BOMB;
        static const Item INCREASE_RANGE;
        static const Item REMOTE;
        
        Item();
        Item(const Item& other);
        
        bool operator==(const Item& other) const;
        bool operator!=(const Item& other) const;
        
        int id() const;
        Coordinate getPosition() const;
        
        static Item create(const Item& item, Coordinate position);
        
    private:
        Item(int value, Coordinate position = Coordinate::ZERO);
        Coordinate position;
        int _value;
    };
}

#endif //__Item__hpp__
