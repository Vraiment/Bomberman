//
//  PlayerCommand.hpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __PlayerCommand__hpp__
#define __PlayerCommand__hpp__

#include "../../Core/Command.hpp"

#include <memory>
#include <string>
#include <vector>

namespace Bomberman {
    class Player;
    class TileMap;
    
    class PlayerCommand : public Command {
    public:
        PlayerCommand(std::shared_ptr<Player> player, std::shared_ptr<TileMap> tileMap, std::string command, std::vector<std::string> arguments);
        
        void execute();
        
    private:
        void move();
        void setBomb();
        
        std::shared_ptr<TileMap> tileMap;
        std::shared_ptr<Player> player;
        std::string command;
        std::vector<std::string> arguments;
    };
}

#endif //__PlayerCommand__hpp__
