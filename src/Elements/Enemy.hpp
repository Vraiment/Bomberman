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
		Enemy(std::string type, Coordinate position = Coordinate());
		
		std::string getType() const;
		Coordinate getPosition() const;
		
		void setPosition(Coordinate position);
		
	private:
		Coordinate position;
		std::string type;
	};
}

#endif // __Enemy_hpp__
