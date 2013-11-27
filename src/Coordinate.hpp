//
//  Coordinate.hpp
//  Bomberman
//
//  Created on 06/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Coordinate__hpp__
#define __Coordinate__hpp__

#include <string>

namespace Bomberman {
	struct Coordinate {
		Coordinate();
		Coordinate(int val);
		Coordinate(int i, int j);
		
		int i, j;
		
		bool operator==(const Coordinate& other) const;
		bool operator!=(const Coordinate& other) const;
		
		std::string toString() const;
	};
}

#endif //__Coordinate__hpp__
