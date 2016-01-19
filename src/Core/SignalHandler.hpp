//
//  SignalHandler.hpp
//  Bomberman
//
//  Created on 19/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#ifndef __SignalHandler__hpp__
#define __SignalHandler__hpp__

#include "ScreenComponent.hpp"

namespace Bomberman {
    enum class Signal;
    
    class SignalHandler : public ScreenComponent {
    public:
        virtual ~SignalHandler();
        
        virtual void handleSignal(Signal signal) = 0;
    };
}

#endif //__SignalHandler__hpp__
