//
//  PlayerCommand.cpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "PlayerCommand.hpp"

#include "../Constants.hpp"
#include "../Elements/Bomb.hpp"
#include "../Elements/Brick.hpp"
#include "../Elements/Player.hpp"
#include "../Log/Log.hpp"
#include "../Log/LogLevel.hpp"
#include "../Map/TileMap.hpp"
#include "../Utils/Exception.hpp"

using namespace std;
using namespace Bomberman::Constants;

namespace Bomberman {
	PlayerCommand::PlayerCommand(shared_ptr<Player> player, shared_ptr<TileMap> tileMap, string command, vector<string> arguments) : player(player), tileMap(tileMap), command(command), arguments(arguments) {
		
	}
	
	void PlayerCommand::execute() {
		if (command == MSG_MOVE) {
			move();
		} else if (command == MSG_SETBOMB) {
			setBomb();
		} else {
			Log::get() << "Invalid command \"" << OBJ_PLAYER << "" << command << "()\"." << LogLevel::error;
		}
		
		_finished = true;
	}
	
	void PlayerCommand::move() {
		bool error = false;
		
		Coordinate newPosition;
		
		if (arguments.size() == 1) {
			string direction = arguments[0];
			
			newPosition = player->position();
			
			if (direction == ARG_RIGHT) {
				++newPosition.i;
			} else if (direction == ARG_UP) {
				--newPosition.j;
			} else if (direction == ARG_LEFT) {
				--newPosition.i;
			} else if (direction == ARG_DOWN) {
				++newPosition.j;
			} else {
				error = true;
			}
		} else if (arguments.size() == 2) {
			throw NotImplementedException();
		}
		
		if (!tileMap->area().contains(newPosition)) {
			return;
		}
		
		if (tileMap->tileHasBrick(newPosition) || tileMap->tileHasBomb(newPosition)) {
			return;
		}
		
		player->position() = newPosition;
		
		if (error) {
			Log::get() << "Invalid arguments for \"" << OBJ_PLAYER << "." << MSG_MOVE << "()\"" << LogLevel::error;
		}
	}
	
	void PlayerCommand::setBomb() {
		if (!arguments.empty()) {
			Log::get() << "Invalid arguments for \"" << OBJ_PLAYER << "." << MSG_SETBOMB << "()\"" << LogLevel::error;
		}
		
		if (!tileMap->tileHasBomb(player->position())) {
			tileMap->addBomb(Bomb(player->position()));
		}
	}
}
