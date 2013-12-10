//
//  Coordinate.cpp
//  Bomberman
//
//  Created on 06/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Coordinate.hpp"

#include <sstream>

using namespace std;

namespace Bomberman {
	Coordinate::Coordinate() : i(0), j(0) {
		
	}
	
	Coordinate::Coordinate(int val) : i(val), j(val) {
		
	}
	
	Coordinate::Coordinate(int i, int j) : i(i), j(j) {
		
	}
	
	bool Coordinate::operator==(Coordinate other) const {
		return i == other.i && j == other.j;
	}
	
	bool Coordinate::operator!=(Coordinate other) const {
		return !(*this == other);
	}
	
	Coordinate& Coordinate::operator+=(Coordinate other) {
		i += other.i;
		j += other.j;
		
		return *this;
	}
	
	Coordinate& Coordinate::operator-=(Coordinate other) {
		i -= other.i;
		j -= other.j;
		
		return *this;
	}
	
	Coordinate& Coordinate::operator*=(Coordinate other) {
		i *= other.i;
		j *= other.j;
		
		return *this;
	}
	
	string Coordinate::toString() const {
		stringstream s;
		
		s << "[" << i << ", " << j << "]";
		
		return s.str();
	}
	
	Coordinate operator+(Coordinate left, Coordinate right) {
		left += right;
		
		return left;
	}
	
	Coordinate operator-(Coordinate left, Coordinate right) {
		left -= right;
		
		return left;
	}
	
	Coordinate operator*(Coordinate left, Coordinate right) {
		left *= right;
		
		return left;
	}
}
