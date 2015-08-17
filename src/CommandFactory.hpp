//
//  CommandFactory.hpp
//  Bomberman
//
//  Created on 16/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __CommandFactory__hpp__
#define __CommandFactory__hpp__

#include <string>
#include <vector>

namespace Bomberman {
	class Command;
	class LoopQuiter;
	class Player;
	class TileMap;
	
	class CommandFactory {
	public:
		~CommandFactory();
		
		void setPlayer(std::shared_ptr<Player> player);
		
		void setTileMap(std::shared_ptr<TileMap> tileMap);
		
		void setLoopQuiter(std::shared_ptr<LoopQuiter> loopQuiter);
		
		std::shared_ptr<Command> call(std::string function, std::vector<std::string> arguments);
		
		std::shared_ptr<Command> sendMessage(std::string receiver, std::string message, std::vector<std::string> arguments = { });
		
	private:
		std::shared_ptr<Player> player;
		std::shared_ptr<TileMap> tileMap;
		std::shared_ptr<LoopQuiter> loopQuiter;
	};
}

#endif //__CommandFactory__hpp__
