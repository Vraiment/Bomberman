//
//  CommandQueue.cpp
//  Bomberman
//
//  Created on 09/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "CommandQueue.hpp"

#include "Command.hpp"
#include "Log/Log.hpp"
#include "Log/LogLevel.hpp"

using namespace std;

namespace Bomberman {
    void CommandQueue::addCommand(shared_ptr<Command> command) {
        if (!command) {
            Log::get() << "Inserting empty command." << LogLevel::error;
            
            return;
        }
        
        commands.push(command);
    }
    
    void CommandQueue::update() {
        if (commands.empty()) {
            return;
        }
        
        if (commands.front()->finished()) {
            commands.pop();
        } else {
            commands.front()->execute();
        }
    }
}
