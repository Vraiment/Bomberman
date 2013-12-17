//
//  PlayerCommand.hpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __PlayerCommand__hpp__
#define __PlayerCommand__hpp__

#include "../Command.hpp"

#include <string>
#include <vector>

namespace Bomberman {
	class Player;
	
	class PlayerCommand : public Command {
	public:
		PlayerCommand(std::shared_ptr<Player> player, std::string command, std::vector<std::string> arguments);
		
		void execute();
		
	private:
		void move();
		
		std::shared_ptr<Player> player;
		std::string command;
		std::vector<std::string> arguments;
	};
}

#endif //__PlayerCommand__hpp__
