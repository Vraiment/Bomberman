//
//  TileMapBuilder.hpp
//  Bomberman
//
//  Created on 17/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __TileMapBuilder__hpp__
#define __TileMapBuilder__hpp__

#include <string>
#include <vector>

namespace Bomberman {
	class Brick;
	class Player;
	
	class TileMapBuilder {
	public:
		virtual ~TileMapBuilder() { }
		
		virtual int width() const = 0;
		virtual int height() const = 0;
		virtual std::string name() const = 0;
		virtual std::vector<Brick> bricks() const = 0;
		virtual std::shared_ptr<Player> player() const = 0;
	};
}

#endif //__TileMapBuilder__hpp__