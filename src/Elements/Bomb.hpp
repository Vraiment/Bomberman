//
//  Bomb.hpp
//  Bomberman
//
//  Created on 17/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#ifndef __Bomb_hpp__
#define __Bomb_hpp__

#include "../Math/Coordinate.hpp"

namespace Bomberman {
	class Bomb {
	public:
		Bomb(Coordinate position);
		
		Coordinate getPosition() const;
		
		void update();
		
		bool exploded() const;
		
	private:
		static const int TTL;
		
		int _startTime, _ttl;
		Coordinate _position;
		bool _counting, _exploded;
	};
}

#endif // __Bomb_hpp__
