//
//  Enemy.hpp
//  Bomberman
//
//  Created on 30/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#ifndef __Enemy_hpp__
#define __Enemy_hpp__

#include "../Timer.hpp"
#include "../Math/Coordinate.hpp"

#include <memory>

namespace Bomberman {
	class TileMap;
	
	class Enemy {
	public:
		Enemy(std::string type, Coordinate position = Coordinate());
		
		void update(std::shared_ptr<TileMap> tileMap);
		
		std::string getType() const;
		Coordinate getPosition() const;
		
		void setPosition(Coordinate position);
		void setSpeed(int speed);
		
	private:
		Timer timer;
		Coordinate position;
		int speed;
		std::string type;
		
		void randomMove(std::shared_ptr<TileMap> tileMap);
	};
}

#endif // __Enemy_hpp__
