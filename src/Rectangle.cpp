//
//  Rectangle.cpp
//  Bomberman
//
//  Created on 12/3/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Rectangle.hpp"

#include "Exception.hpp"

namespace Bomberman {
	Rectangle::Rectangle() : Coordinate(), width(0), height(0) {
		
	}
	
	Rectangle::Rectangle(int i, int j, int width, int height) : Coordinate(i, j), width(width), height(height) {
		
	}
	
	Coordinate Rectangle::leftTop() const {
		return Coordinate(i, j);
	}
	
	Coordinate Rectangle::rightTop() const {
		return Coordinate(i + width - 1, j);
	}
	
	Coordinate Rectangle::rightBottom() const {
		return Coordinate(i + width - 1, j + height - 1);
	}
	
	Coordinate Rectangle::leftBottom() const {
		return Coordinate(i, j + height - 1);
	}
	
	bool Rectangle::intersects(Rectangle other) const {
		return
			contains(other.leftTop()) ||
			contains(other.rightTop()) ||
			contains(other.leftBottom()) ||
			contains(other.rightBottom()) ||
			other.contains(leftTop()) ||
			other.contains(rightTop()) ||
			other.contains(rightBottom()) ||
			other.contains(leftBottom());
	}
	
	bool Rectangle::contains(int i, int j) const {
		return
			(i >= this->i) &&
			(i < (this->i + width)) &&
			(j >= this->j) &&
			(j < (this->j + height));
	}
	
	bool Rectangle::contains(Coordinate coordinate) const {
		return contains(coordinate.i, coordinate.j);
	}
	
	bool Rectangle::operator==(const Rectangle& other) const {
		return
			static_cast<Coordinate>(*this) == static_cast<Coordinate>(other) &&
			width == other.width &&
			height == other.height;
	}
	
	bool Rectangle::operator!=(const Rectangle& other) const {
		return !(*this == other);
	}
}
