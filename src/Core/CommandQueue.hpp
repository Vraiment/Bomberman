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

namespace Bomberman {
    class Command;
    
    class CommandQueue {
    public:
        void addCommand(std::shared_ptr<Command> command);
        
        void update();
        
    private:
        std::queue<std::shared_ptr<Command>> commands;
    };
}

#endif //__CommandQueue__hpp__
