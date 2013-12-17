//
//  CommandFactory.cpp
//  Bomberman
//
//  Created on 16/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "CommandFactory.hpp"

#include "Commands/PlayerCommand.hpp"
#include "Elements/Player.hpp"
#include "Log/Log.hpp"
#include "Log/LogLevel.hpp"
#include "Utils/Exception.hpp"

using namespace std;

namespace Bomberman {
	CommandFactory::~CommandFactory() {
		
	}
	
	void CommandFactory::setPlayer(shared_ptr<Player> player) {
		this->player = player;
	}
	
	void CommandFactory::setTileMap(shared_ptr<TileMap> tileMap) {
		this->tileMap = tileMap;
	}
	
	shared_ptr<Command> CommandFactory::call(string function, vector<string> arguments) {
		throw NotImplementedException();
	}
	
	shared_ptr<Command> CommandFactory::sendMessage(string receiver, string message, vector<string> arguments) {
		shared_ptr<Command> result;
		
		if (receiver == "player") {
			result.reset(new PlayerCommand(player, tileMap, message, arguments));
		} else {
			throw InvalidReceiverException();
		}
		
		return result;
	}
}
