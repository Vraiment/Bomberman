//
//  Coordinate.hpp
//  Bomberman
//
//  Created on 06/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Coordinate__hpp__
#define __Coordinate__hpp__

#include <array>
#include <string>

namespace Bomberman {
	struct Coordinate {
		Coordinate();
		Coordinate(int val);
		Coordinate(int i, int j);
		
		int i, j;
		
		Coordinate absolute() const;
		
		Coordinate left() const;
		Coordinate right() const;
		Coordinate up() const;
		Coordinate down() const;
		
		Coordinate leftUp() const;
		Coordinate rightUp() const;
		Coordinate leftDown() const;
		Coordinate rightDown() const;
		
		Coordinate normalize() const;
		
		std::array<Coordinate, 4> cross() const;
		std::array<Coordinate, 8> adjacents() const;
		
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
