//
//  Coordinate.cpp
//  Bomberman
//
//  Created on 06/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Coordinate.hpp"

#include <cmath>
#include <sstream>

using namespace std;

namespace Bomberman {
	Coordinate::Coordinate() : i(0), j(0) {
		
	}
	
	Coordinate::Coordinate(int val) : i(val), j(val) {
		
	}
	
	Coordinate::Coordinate(int i, int j) : i(i), j(j) {
		
	}
	
	Coordinate Coordinate::absolute() const {
		return Coordinate(abs(i), abs(j));
	}
	
	Coordinate Coordinate::left() const {
		return Coordinate(i - 1, j);
	}
	
	Coordinate Coordinate::right() const {
		return Coordinate(i + 1, j);
	}
	
	Coordinate Coordinate::up() const {
		return Coordinate(i, j - 1);
	}
	
	Coordinate Coordinate::down() const {
		return Coordinate(i, j + 1);
	}
	
	Coordinate Coordinate::leftUp() const {
		return Coordinate(i - 1, j - 1);
	}
	
	Coordinate Coordinate::rightUp() const {
		return Coordinate(i + 1, j - 1);
	}
	
	Coordinate Coordinate::leftDown() const {
		return Coordinate(i - 1, j + 1);
	}
	
	Coordinate Coordinate::rightDown() const {
		return Coordinate(i + 1, j + 1);
	}
	
	array<Coordinate, 4> Coordinate::cross() const {
		return {
			left(), right(), up(), down()
		};
	}
	
	array<Coordinate, 8> Coordinate::adjacents() const {
		return {
			left(), right(), up(), down(),
			leftUp(), rightUp(), leftDown(), rightDown()
		};
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
	
	Coordinate& Coordinate::operator/=(Coordinate other) {
		i /= other.i;
		j /= other.j;
		
		return *this;
	}
	
	string Coordinate::toString() const {
		stringstream s;
		
		s << "[" << i << ", " << j << "]";
		
		return s.str();
	}
	
	Coordinate operator-(Coordinate coordinate) {
		coordinate.i = -coordinate.i;
		coordinate.j = -coordinate.j;
		
		return coordinate;
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
	
	Coordinate operator/(Coordinate left, Coordinate right) {
		left /= right;
		
		return left;
	}
}
