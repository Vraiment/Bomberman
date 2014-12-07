//
//  Player.hpp
//  Bomberman
//
//  Created on 12/6/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Player__hpp__
#define __Player__hpp__

#include "../Timer.hpp"
#include "../Math/Coordinate.hpp"

namespace Bomberman {
	class Player {
	public:
		Player();
		
		Coordinate& position();
		
		void update();
		
		int getExplosionSize() const;
		int maxBombs() const;
		
		bool isDead() const;
		bool isInvencible() const;
		void die();
		void respawn();
		
	private:
		static const int invencibleTime;
		
		Coordinate _position;
		Timer invencible;
		int explosionSize;
		int _maxBombs;
		bool dead;
	};
}

#endif //__Player__hpp__
