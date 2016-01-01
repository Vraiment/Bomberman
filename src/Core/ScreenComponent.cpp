//
//  ScreenComponent.cpp
//  Bomberman
//
//  Created on 31/12/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "ScreenComponent.hpp"

namespace Bomberman {
    ScreenComponent::ScreenComponent() : enabled(true), finished(false) {
        
    }
    
    ScreenComponent::~ScreenComponent() {
        
    }
    
    bool ScreenComponent::isEnabled() const {
        return enabled;
    }
    
    void ScreenComponent::enable() {
        enabled = true;
    }
    
    void ScreenComponent::disable() {
        enabled = false;
    }
    
    bool ScreenComponent::isFinished() const {
        return finished;
    }
    
    void ScreenComponent::finish() {
        finished = true;
    }
}
