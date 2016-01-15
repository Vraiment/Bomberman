//
//  QuitCommand.hpp
//  Bomberman
//
//  Created on 17/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __QuitCommand__hpp__
#define __QuitCommand__hpp__

#include "../../Core/Command.hpp"

#include <memory>

namespace Bomberman {
    class LoopQuiter;
    
    class QuitCommand : public Command {
    public:
        QuitCommand(std::shared_ptr<LoopQuiter> loopQuiter);
        
        void execute();
        
    private:
        std::shared_ptr<LoopQuiter> loopQuiter;
    };
}

#endif //__QuitCommand__hpp__
