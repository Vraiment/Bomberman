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
		// Config file
		const char CFG_NULLFILE[] = "/dev/null";
		const char CFG_VIEWPORT[] = "viewport";
		const char CFG_TITLE[] = "title";
		const char CFG_WIDTH[] = "width";
		const char CFG_HEIGHT[] = "height";
		const char CFG_LOGGERS[] = "loggers";
		const char CFG_LOGGER[] = "logger";
		
		// Receivers
		const char OBJ_PLAYER[] = "player";
		
		// Messages
		const char MSG_MOVE[] = "move";
		
		// Arguments
		const char ARG_RIGHT[] = "right";
		const char ARG_LEFT[] = "left";
		const char ARG_UP[] = "up";
		const char ARG_DOWN[] = "down";
		
		// Dirs & files
		const char DIR_TEXTURES[] = "textures";
	};
}

#endif //__Constants__hpp__
