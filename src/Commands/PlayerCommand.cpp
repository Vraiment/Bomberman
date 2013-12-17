//
//  PlayerCommand.cpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "PlayerCommand.hpp"

#include "../TileMap.hpp"
#include "../Elements/Brick.hpp"
#include "../Elements/Player.hpp"
#include "../Log/Log.hpp"
#include "../Log/LogLevel.hpp"
#include "../Utils/Exception.hpp"

using namespace std;

namespace Bomberman {
	PlayerCommand::PlayerCommand(shared_ptr<Player> player, shared_ptr<TileMap> tileMap, string command, vector<string> arguments) : player(player), tileMap(tileMap), command(command), arguments(arguments) {
		
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
		
		Coordinate newPosition;
		
		if (arguments.size() == 1) {
			string direction = arguments[0];
			
			newPosition = player->position();
			
			if (direction == "right") {
				++newPosition.i;
			} else if (direction == "up") {
				--newPosition.j;
			} else if (direction == "left") {
				--newPosition.i;
			} else if (direction == "down") {
				++newPosition.j;
			} else {
				error = true;
			}
		} else if (arguments.size() == 2) {
			throw NotImplementedException();
		}
		
		auto bricks = tileMap->bricks();
		for (auto brick = bricks.begin(); brick != bricks.end(); ++brick) {
			if (newPosition == brick->position()) {
				return;
			}
		}
		
		player->position() = newPosition;
		
		if (error) {
			Log::get() << "Invalid arguments for \"player.move()\"" << LogLevel::error;
		}
	}
}
