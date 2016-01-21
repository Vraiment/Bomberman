//
//  InGameCommandQueue.hpp
//  Bomberman
//
//  Created on 20/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#ifndef __InGameCommandQueue__hpp__
#define __InGameCommandQueue__hpp__

#include "../Core/CommandQueue.hpp"
#include "../Core/SignalHandler.hpp"

namespace Bomberman {
    class InGameCommandQueue : public CommandQueue, public SignalHandler {
    public:
        void handleSignal(Signal signal);
    };
}

#endif //__InGameCommandQueue__hpp__
