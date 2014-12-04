//
//  TxtTileMapLoader.hpp
//  Bomberman
//
//  Created on 09/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#include "TxtTileMapLoader.hpp"

#include "../Constants.hpp"
#include "../Elements/Brick.hpp"
#include "../Elements/Enemy.hpp"
#include "../Elements/Player.hpp"
#include "../Log/Log.hpp"
#include "../Log/LogLevel.hpp"
#include "../Utils/Exception.hpp"
#include "../Utils/StringUtils.hpp"
#include "../Utils/OperatingSystem.hpp"
#include "DummyTileMapBuilder.hpp"

#include <fstream>
#include <sstream>

using namespace std;
using namespace Bomberman::Constants;

namespace Bomberman {
	class CommandReader {
	public:
		CommandReader(string str) : _validCommand(false) {
			vector<string> tokens = StringUtils::split(str, ' ');
			
			if (tokens.empty()) {
				_validCommand = false;
				return;
			}
			
			_command = tokens[0];
			
			for (int n = 1; n < tokens.size(); ++n) {
				_arguments.push_back(tokens[n]);
			}
			
			verifyCommand();
		}
		
		bool validCommand() {
			return _validCommand;
		}
		
		string getCommand() {
			return _command;
		}
		
		vector<string> getArguments() {
			return _arguments;
		}
		
	private:
		bool _validCommand;
		string _command;
		vector<string> _arguments;
		
		void verifyCommand() {
			if (_command == MAP_CMD_NAME) {
				_validCommand = !_arguments.empty();
			} else if (_command == MAP_CMD_ENEMY_RANGE) {
				_validCommand = _arguments.size() == 2;
			} else if (_command == MAP_CMD_ENEMY) {
				_validCommand = _arguments.size() == 3;
			} else if (_command == MAP_CMD_PLAYER) {
				_validCommand = _arguments.size() == 2;
			} else if (_command == MAP_CMD_SIZE) {
				_validCommand = _arguments.size() == 2;
			} else if (_command == MAP_CMD_SINGLE) {
				_validCommand = _arguments.size() == 3;
			} else if (_command == MAP_CMD_LINE) {
				_validCommand = _arguments.size() == 5;
			} else {
				_validCommand = false;
			}
		}
	};
	
	void printError(string line) {
		Log::get() << "Invalid command in map file: " << line << LogLevel::error;
	}
	
	bool buildCoordinate(string i, string j, Coordinate& coordinate) {
		try {
			coordinate.i = stoi(i);
			coordinate.j = stoi(j);
		} catch (logic_error& exception) {
			return false;
		}
		
		return true;
	}
	
	TxtTileMapLoader::~TxtTileMapLoader() {
		
	}
	
	shared_ptr<TileMapBuilder> TxtTileMapLoader::load(string fileName) {
		ifstream file(getPath({"maps"}, fileName));
		
		if (file) {
			Log::get() << "Reading map file: " << fileName << LogLevel::info;
		} else {
			Log::get() << "Could not open file: " << fileName << OpeningFileErrorException();
		}
		
		_builder.reset(new DummyTileMapBuilder());
		
		string line;
		while (getline(file, line)) {
			line = StringUtils::trim(line);
			
			if (line.empty() || line[0] == '#') {
				continue;
			}
			
			CommandReader commandReader(line);
			string command = commandReader.getCommand();
			vector<string> arguments = commandReader.getArguments();
			
			if (!(commandReader.validCommand() && processCommand(command, arguments))) {
				printError(line);
				continue;
			}
		}
		
		return _builder;
	}
	
	bool TxtTileMapLoader::processCommand(string command, vector<string> arguments) {
		DummyTileMapBuilder *builder = static_cast<DummyTileMapBuilder *>(_builder.get());
		
		if (command == MAP_CMD_NAME) {
			builder->_name = StringUtils::join(arguments, ' ');
		} else if (command == MAP_CMD_ENEMY_RANGE) {
			int range;
			
			if (!StringUtils::tryParseInt(arguments[1], range)) {
				return false;
			}
			
			if (arguments[0] == ENEMY_EASY) {
				builder->enemiesRange.easy = range;
			} else if (arguments[0] == ENEMY_MEDIUM) {
				builder->enemiesRange.medium = range;
			} else if (arguments[0] == ENEMY_HARD) {
				builder->enemiesRange.hard = range;
			} else {
				return false;
			}
		} else if (command == MAP_CMD_ENEMY) {
			if (arguments[0] != ENEMY_EASY && arguments[0] != ENEMY_MEDIUM && arguments[0] != ENEMY_HARD) {
				return false;
			}
			
			Coordinate position;
			if (!buildCoordinate(arguments[1], arguments[2], position)) {
				return false;
			}
			
			Enemy enemy(arguments[0], position);
			
			builder->_enemies.push_back(enemy);
		} else if (command == MAP_CMD_PLAYER) {
			shared_ptr<Player> player(new Player());
			
			if (!buildCoordinate(arguments[0], arguments[1], player->position())) {
				return false;
			}
			
			builder->_player = player;
		} else if (command == MAP_CMD_SIZE) {
			Coordinate coordinate;
			
			if (!buildCoordinate(arguments[0], arguments[1], coordinate)) {
				return false;
			}
			
			builder->_width = coordinate.i;
			builder->_height = coordinate.j;
		} else if (command == MAP_CMD_SINGLE) {
			Coordinate coordinate;
			
			if (!buildCoordinate(arguments[1], arguments[2], coordinate)) {
				return false;
			}
			
			if (arguments[0] == MAP_OBJ_COMMON_BRICK) {
				builder->_bricks.push_back(Brick(coordinate));
			} else if (arguments[0] == MAP_OBJ_DESTRUCT_BRICK) {
				builder->_bricks.push_back(Brick(coordinate, true));
			} else {
				return false;
			}
		} else if (command == MAP_CMD_LINE) {
			Coordinate start, end;
			
			if (!buildCoordinate(arguments[1], arguments[2], start)) {
				return false;
			}
			if (!buildCoordinate(arguments[3], arguments[5], end)) {
				return false;
			}
			
			if (start.i > end.i) {
				swap(start.i, end.i);
			}
			
			if (start.j > end.j) {
				swap(start.j, end.j);
			}
			
			bool destructible;
			if (arguments[0] == MAP_OBJ_COMMON_BRICK) {
				destructible = false;
			} else if (arguments[0] == MAP_OBJ_DESTRUCT_BRICK) {
				destructible = true;
			} else {
				return false;
			}
			
			Coordinate pos;
			for (pos.i = start.i; pos.i < end.i; ++pos.i) {
				for (pos.j = start.j; pos.j < end.j; ++pos.j) {
					builder->_bricks.push_back(Brick(pos, destructible));
				}
			}
		} else {
			return false;
		}
		
		return true;
	}
}
