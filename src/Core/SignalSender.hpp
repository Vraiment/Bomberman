//
//  SignalSender.hpp
//  Bomberman
//
//  Created on 19/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#ifndef __SignalSender__hpp__
#define __SignalSender__hpp__

namespace Bomberman {
    enum class Signal;
    
    class SignalSender {
    public:
        virtual ~SignalSender();
        
        virtual void sendSignal(Signal signal) = 0;
    };
}

#endif //__SignalSender__hpp__
