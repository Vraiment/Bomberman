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
#include "../Elements/Player.hpp"
#include "../Log/Log.hpp"
#include "../Log/LogLevel.hpp"
#include "../Utils/Exception.hpp"
#include "../Utils/StringUtils.hpp"
#include "../Utils/OperatingSystem.hpp"
#include "TileMapBuilder.hpp"

#include <fstream>
#include <sstream>

using namespace std;
using namespace Bomberman::Constants;

namespace Bomberman {
	class Builder : public TileMapBuilder {
	public:
		int _width = 0, _height = 0;
		string _name;
		vector<Brick> _bricks;
		shared_ptr<Player> _player;
		
		int width() const {
			return _width;
		}
		
		int height() const {
			return _height;
		}
		
		string name() const {
			return _name;
		}
		
		vector<Brick> bricks() const {
			return _bricks;
		}
		
		shared_ptr<Player> player() const {
			return _player;
		}
	};
	
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
			} else if (_command == MAP_CMD_PLAYER) {
				_validCommand = _arguments.size() == 2;
			} else if (_command == MAP_CMD_SIZE) {
				_validCommand = _arguments.size() == 2;
			} else if (_command == MAP_CMD_SINGLE) {
				_validCommand = _arguments.size() == 3;
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
		
		_builder.reset(new Builder());
		
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
		Builder *builder = static_cast<Builder *>(_builder.get());
		
		if (command == MAP_CMD_NAME) {
			builder->_name = StringUtils::join(arguments, ' ');
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
		} else {
			return false;
		}
		
		return true;
	}
}