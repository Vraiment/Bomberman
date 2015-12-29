//
//  LayerManager.hpp
//  Bomberman
//
//  Created on 27/12/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __LayerManager__hpp__
#define __LayerManager__hpp__

#include <memory>
#include <queue>

namespace Bomberman {
    class Layer;
    
    class LayerQueue {
    public:
        virtual ~LayerQueue();
        
        void addLayer(std::shared_ptr<Layer> layer);
        
    protected:
        std::queue<std::shared_ptr<Layer>> layers;
    };
}

#endif //__LayerManager__hpp__
