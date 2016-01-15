//
//  QuitCommand.cpp
//  Bomberman
//
//  Created on 17/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "QuitCommand.hpp"

#include "../../Core/LoopQuiter.hpp"

using namespace std;

namespace Bomberman {
    QuitCommand::QuitCommand(shared_ptr<LoopQuiter> loopQuiter) : loopQuiter(loopQuiter) {
        
    }
    
    void QuitCommand::execute() {
        loopQuiter->quitLoop();
        _finished = true;
    }
}
