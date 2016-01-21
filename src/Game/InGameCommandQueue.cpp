//
//  InGameCommandQueue.cpp
//  Bomberman
//
//  Created on 20/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#include "InGameCommandQueue.hpp"

#include "Signal.hpp"

namespace Bomberman {
    void InGameCommandQueue::handleSignal(Signal signal)  {
        if (signalIn(signal, { Signal::InGame, Signal::ShowConsole, Signal::HideConsole, Signal::PlayerAlive, Signal::PlayerDead })) {
            Updatable::enable();
        } else {
            Updatable::disable();
        }
    }
}
