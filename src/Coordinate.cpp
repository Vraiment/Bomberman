//
//  Coordinate.cpp
//  Bomberman
//
//  Created on 06/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Coordinate.hpp"

namespace Bomberman {
	Coordinate::Coordinate() : i(0), j(0) {
		
	}
	
	Coordinate::Coordinate(int val) : i(val), j(val) {
		
	}
	
	Coordinate::Coordinate(int i, int j) : i(i), j(j) {
		
	}
}
