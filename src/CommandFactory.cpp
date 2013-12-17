//
//  CommandFactory.cpp
//  Bomberman
//
//  Created on 16/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "CommandFactory.hpp"

#include "Utils/Exception.hpp"

using namespace std;

namespace Bomberman {
	shared_ptr<Command> CommandFactory::call(string function, vector<string> arguments) {
		throw NotImplementedException();
	}
	
	shared_ptr<Command> CommandFactory::sendMessage(string receiver, string message, vector<string> arguments) {
		throw NotImplementedException();
	}
}
