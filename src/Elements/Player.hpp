//
//  Player.hpp
//  Bomberman
//
//  Created on 12/6/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Player__hpp__
#define __Player__hpp__

#include "../Math/Coordinate.hpp"

namespace Bomberman {
	class Player {
	public:
		Player();
		
		Coordinate& position();
		
		int getExplosionSize() const;
		int maxBombs() const;
		
		bool isDead() const;
		void die();
		void respawn();
		
	private:
		Coordinate _position;
		int explosionSize;
		int _maxBombs;
		bool dead;
	};
}

#endif //__Player__hpp__
