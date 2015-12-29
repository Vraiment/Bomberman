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
        
        // Boolean values
        const std::string BOOL_TRUE = "true";
        const std::string BOOL_FALSE = "false";
        
        // Config file
        const std::string CFG_NULLFILE = "/dev/null";
        const std::string CFG_VIEWPORT = "viewport";
        const std::string CFG_TITLE = "title";
        const std::string CFG_WIDTH = "width";
        const std::string CFG_HEIGHT = "height";
        const std::string CFG_LOGGERS = "loggers";
        const std::string CFG_LOGGER = "logger";
        
        // Map file
        const std::string MAP_CMD_NAME = "name";
        const std::string MAP_CMD_ENEMY = "enemy";
        const std::string MAP_CMD_ENEMY_RANGE = "enemy_range";
        const std::string MAP_CMD_ENEMY_SPEED = "enemy_speed";
        const std::string MAP_CMD_PLAYER = "player";
        const std::string MAP_CMD_SIZE = "size";
        const std::string MAP_CMD_SINGLE = "single";
        const std::string MAP_CMD_LINE = "line";
        const std::string MAP_CMD_ITEM = "item";
        const std::string MAP_OBJ_COMMON_BRICK = "common_brick";
        const std::string MAP_OBJ_DESTRUCT_BRICK = "destruct_brick";
        const std::string MAP_ITEM_EXTRA_BOMB = "extra_bomb";
        const std::string MAP_ITEM_INCREASE_RANGE = "increase_range";
        const std::string MAP_ITEM_REMOTE = "remote";
        
        // Functions
        const std::string FUNC_EXIT = "exit";
        
        // Receivers
        const std::string OBJ_PLAYER = "player";
        
        // Messages
        const std::string MSG_MOVE = "move";
        const std::string MSG_SETBOMB = "setbomb";
        const std::string MSG_IGNITE = "ignite";
        const std::string MSG_EXTRA_BOMB = "extra_bomb";
        const std::string MSG_INCREASE_RANGE = "increase_range";
        const std::string MSG_IVINCIBLE = "invincible";
        const std::string MSG_REMOTE = "remote";
        
        // Arguments
        const std::string ARG_RIGHT = "right";
        const std::string ARG_LEFT = "left";
        const std::string ARG_UP = "up";
        const std::string ARG_DOWN = "down";
        
        // Dirs & files
        const std::string DIR_RESOURCES = "resources";
        const std::string DIR_FONTS = "fonts";
        const std::string DIR_TEXTURES = "textures";
        
        // Enemy types
        const std::string ENEMY_EASY = "easy";
        const std::string ENEMY_MEDIUM = "medium";
        const std::string ENEMY_HARD = "hard";
    };
}

#endif //__Constants__hpp__
