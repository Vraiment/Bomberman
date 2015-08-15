//
//  Item.hpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __Item__hpp__
#define __Item__hpp__

namespace Bomberman {
	class Item {
	public:
		static const Item EXTRA_BOMB;
		static const Item INCREASE_RANGE;
		
		Item(const Item& other);
		
		bool operator==(const Item& other) const;
		bool operator!=(const Item& other) const;
		
		int id() const;
		
	private:
		Item(int value);
		int _value;
	};
}

#endif //__Item__hpp__
