//
//  GameOverCommand.cpp
//  Bomberman
//
//  Created on 01/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#include "GameOverCommand.hpp"

#include "../Console.hpp"
#include "../Map/TileMap.hpp"

using namespace std;

namespace Bomberman {
    GameOverCommand::GameOverCommand(shared_ptr<Console> console, shared_ptr<TileMap> tileMap) : console(console), tileMap(tileMap) {
        
    }
    
    void GameOverCommand::execute() {
        if (console->visible()) {
            console->hide();
        }
        
        tileMap->endGame();
        
        _finished = true;
    }
}
