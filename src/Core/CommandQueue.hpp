//
//  CommandQueue.hpp
//  Bomberman
//
//  Created on 09/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __CommandQueue__hpp__
#define __CommandQueue__hpp__

#include <memory>
#include <queue>

#include "Updatable.hpp"

namespace Bomberman {
    class Command;
    
    class CommandQueue : public Updatable {
    public:
        void addCommand(std::shared_ptr<Command> command);
        
        void update();
        
        void clear();
        
    private:
        std::queue<std::shared_ptr<Command>> commands;
    };
}

#endif //__CommandQueue__hpp__
