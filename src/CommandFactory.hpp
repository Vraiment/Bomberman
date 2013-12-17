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
	
	class CommandFactory {
	public:
		std::shared_ptr<Command> call(std::string function, std::vector<std::string> arguments);
		
		std::shared_ptr<Command> sendMessage(std::string receiver, std::string message, std::vector<std::string> arguments);
	};
}

#endif //__CommandFactory__hpp__
