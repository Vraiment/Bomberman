//
//  Item.cpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "Item.hpp"

namespace Bomberman {
	Item::Item(int value) : _value(value) {
		
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
	
	const Item Item::EXTRA_BOMB = Item(0);
	const Item Item::INCREASE_RANGE = Item(1);
}
