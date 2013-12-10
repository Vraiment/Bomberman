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
		Coordinate& position();
		
	private:
		Coordinate _position;
	};
}

#endif //__Player__hpp__
