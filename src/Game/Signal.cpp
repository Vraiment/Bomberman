//
//  Signal.cpp
//  Bomberman
//
//  Created on 21/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#include "Signal.hpp"

namespace Bomberman {
    bool signalIn(Signal signal, std::initializer_list<Signal> signals)  {
        for (auto otherSignal : signals) {
            if (otherSignal == signal) {
                return true;
            }
        }
        
        return false;
    }
}
