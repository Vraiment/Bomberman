//
//  GameOverCommand.hpp
//  Bomberman
//
//  Created on 01/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#ifndef __GameOverCommand__hpp__
#define __GameOverCommand__hpp__

#include "../../Core/Command.hpp"

#include <memory>

namespace Bomberman {
    class Console;
    class TileMap;
    
    class GameOverCommand : public Command {
    public:
        GameOverCommand(std::shared_ptr<Console> consoleLayer, std::shared_ptr<TileMap> tileMap);
        
        void execute();
        
    private:
        std::shared_ptr<Console> console;
        std::shared_ptr<TileMap> tileMap;
    };
}

#endif //__GameOverCommand__hpp__
