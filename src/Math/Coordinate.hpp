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
		
		bool operator==(Coordinate other) const;
		bool operator!=(Coordinate other) const;
		
		Coordinate& operator+=(Coordinate other);
		Coordinate& operator-=(Coordinate other);
		Coordinate& operator*=(Coordinate other);
		Coordinate& operator/=(Coordinate other);
		
		std::string toString() const;
	};
	
	Coordinate operator-(Coordinate coordinate);
	Coordinate operator+(Coordinate left, Coordinate right);
	Coordinate operator-(Coordinate left, Coordinate right);
	Coordinate operator*(Coordinate left, Coordinate right);
	Coordinate operator/(Coordinate left, Coordinate right);
}

#endif //__Coordinate__hpp__
