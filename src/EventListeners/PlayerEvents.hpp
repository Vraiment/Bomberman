//
//  PlayerEvents.hpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __PlayerEvents__hpp__
#define __PlayerEvents__hpp__

#include "../EventListener.hpp"

#include <memory>

namespace Bomberman {
	class TileMap;
	
	class PlayerEvents : public EventListener {
	public:
		PlayerEvents(std::shared_ptr<TileMap> tileMap);
		~PlayerEvents();
		
		void listenEvent(SDL_Event event);
		
	private:
		std::shared_ptr<TileMap> tileMap;
	};
}

#endif //__PlayerEvents__hpp__
