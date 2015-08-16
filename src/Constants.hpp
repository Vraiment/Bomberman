//
//  Constants.hpp
//  Bomberman
//
//  Created on 09/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#ifndef __Constants__hpp__
#define __Constants__hpp__

#include <string>

namespace Bomberman {
	namespace Constants {
		// Tile size
		const int TILE_HEIGHT = 40;
		const int TILE_WIDTH = 40;
		
		// Config file
		const char CFG_NULLFILE[] = "/dev/null";
		const char CFG_VIEWPORT[] = "viewport";
		const char CFG_TITLE[] = "title";
		const char CFG_WIDTH[] = "width";
		const char CFG_HEIGHT[] = "height";
		const char CFG_LOGGERS[] = "loggers";
		const char CFG_LOGGER[] = "logger";
		
		// Map file
		const char MAP_CMD_NAME[] = "name";
		const char MAP_CMD_ENEMY[] = "enemy";
		const char MAP_CMD_ENEMY_RANGE[] = "enemy_range";
		const char MAP_CMD_ENEMY_SPEED[] = "enemy_speed";
		const char MAP_CMD_PLAYER[] = "player";
		const char MAP_CMD_SIZE[] = "size";
		const char MAP_CMD_SINGLE[] = "single";
		const char MAP_CMD_LINE[] = "line";
		const char MAP_OBJ_COMMON_BRICK[] = "common_brick";
		const char MAP_OBJ_DESTRUCT_BRICK[] = "destruct_brick";
		
		// Receivers
		const char OBJ_PLAYER[] = "player";
		
		// Messages
		const char MSG_MOVE[] = "move";
		const char MSG_SETBOMB[] = "setbomb";
		const char MSG_EXTRA_BOMB[] = "extra_bomb";
		const char MSG_INCREASE_RANGE[] = "increase_range";
		
		// Arguments
		const char ARG_RIGHT[] = "right";
		const char ARG_LEFT[] = "left";
		const char ARG_UP[] = "up";
		const char ARG_DOWN[] = "down";
		
		// Dirs & files
		const char DIR_FONTS[] = "fonts";
		const char DIR_TEXTURES[] = "textures";
		
		// Logger types
		const char LOGGER_STD_OUT[] = "STDOUT";
		
		// Enemy types
		const char ENEMY_EASY[] = "easy";
		const char ENEMY_MEDIUM[] = "medium";
		const char ENEMY_HARD[] = "hard";
	};
}

#endif //__Constants__hpp__
