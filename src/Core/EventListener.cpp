//
//  EventListener.cpp
//  Bomberman
//
//  Created on 16/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "EventListener.hpp"

namespace Bomberman {
    EventListener::EventListener() : _enabled(true), _isZombie(false) {
        
    }
    
    bool EventListener::enabled() const {
        return _enabled;
    }
    
    void EventListener::enable() {
        _enabled = true;
    }
    
    void EventListener::disable() {
        _enabled = false;
    }
    
    bool EventListener::isZombie() const {
        return _isZombie;
    }
    
    void EventListener::isZombie(bool isZombie) {
        _isZombie = isZombie;
    }
}
