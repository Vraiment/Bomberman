//
//  Layer.cpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "Layer.hpp"

#include "Math/Rectangle.hpp"

namespace Bomberman {
    Layer::~Layer() {
        
    }
    
    bool Layer::isFinished() const {
        return _isZombie;
    }
    
    void Layer::finish() {
        _isZombie = true;
    }
    
    void Layer::screenSizeChanged(Rectangle previousSize, Rectangle newSize) {
        
    }
    
    bool Layer::shouldDraw() const {
        return _shouldDraw;
    }
    
    void Layer::shouldDraw(bool should) {
        _shouldDraw = should;
    }
    
    bool Layer::shouldUpdate() const {
        return _shouldUpdate;
    }
    
    void Layer::shouldUpdate(bool should) {
        _shouldUpdate = should;
    }
}
