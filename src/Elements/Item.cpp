//
//  Item.cpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "Item.hpp"

namespace Bomberman {
    Item::Item() : _value(-1) {
        
    }
    
    Item::Item(int value, Coordinate position) : _value(value), position(position) {
        
    }
    
    Item::Item(const Item& other) : _value(other._value) {
        
    }
    
    bool Item::operator==(const Item& other) const {
        return _value == other._value;
    }
    
    bool Item::operator!=(const Item& other) const {
        return !(*this == other);
    }
    
    int Item::id() const {
        return _value;
    }
    
    Coordinate Item::getPosition() const {
        return position;
    }
    
    Item Item::create(const Item& item, Coordinate position) {
        return Item(item._value, position);
    }
    
    const Item Item::NONE = Item(-1);
    const Item Item::EXTRA_BOMB = Item(0);
    const Item Item::INCREASE_RANGE = Item(1);
}
