//
//  PlayerCommand.cpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "PlayerCommand.hpp"

#include "../Elements/Player.hpp"
#include "../Log/Log.hpp"
#include "../Log/LogLevel.hpp"
#include "../Utils/Exception.hpp"

using namespace std;

namespace Bomberman {
	PlayerCommand::PlayerCommand(shared_ptr<Player> player, string command, vector<string> arguments) : player(player), command(command), arguments(arguments) {
		
	}
	
	void PlayerCommand::execute() {
		if (command == "move") {
			move();
		} else {
			Log::get() << "Invalid command \"player." << command << "()\"." << LogLevel::error;
		}
		
		_finished = true;
	}
	
	void PlayerCommand::move() {
		bool error = false;
		
		if (arguments.size() == 1) {
			string direction = arguments[0];
			
			if (direction == "right") {
				++player->position().i;
			} else if (direction == "up") {
				--player->position().j;
			} else if (direction == "left") {
				--player->position().i;
			} else if (direction == "down") {
				++player->position().j;
			} else {
				error = true;
			}
		} else if (arguments.size() == 2) {
			throw NotImplementedException();
		}
		
		if (error) {
			Log::get() << "Invalid arguments for \"player.move()\"" << LogLevel::error;
		}
	}
}
