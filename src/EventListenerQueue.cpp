//
//  EventListener.cpp
//  Bomberman
//
//  Created on 28/12/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "EventListenerQueue.hpp"

using namespace std;

namespace Bomberman {
    EventListenerQueue::~EventListenerQueue() {
        
    }
    
    void EventListenerQueue::addEventListener(shared_ptr<EventListener> eventListener) {
        eventListeners.push(eventListener);
    }
}
