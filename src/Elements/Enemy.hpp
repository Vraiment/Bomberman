//
//  Enemy.hpp
//  Bomberman
//
//  Created on 30/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#ifndef __Enemy_hpp__
#define __Enemy_hpp__

#include "../Math/Coordinate.hpp"

#include <memory>

namespace Bomberman {
	class Enemy {
	public:
		Enemy(int range);
		
		int getRange() const;
		Coordinate getPosition() const;
		
		void setPosition(Coordinate position);
		
	private:
		Coordinate position;
		int range;
	};
}

#endif // __Enemy_hpp__
