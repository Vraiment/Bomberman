//
//  LayerManager.cpp
//  Bomberman
//
//  Created on 27/12/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "LayerQueue.hpp"

using namespace std;

namespace Bomberman {
    LayerQueue::~LayerQueue() {
        
    }
    
    void LayerQueue::addLayer(shared_ptr<Layer> layer) {
        layers.push(layer);
    }
}
