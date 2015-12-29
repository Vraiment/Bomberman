//
//  EventListener.hpp
//  Bomberman
//
//  Created on 28/12/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __EventListenerQueue__hpp__
#define __EventListenerQueue__hpp__

#include <memory>
#include <queue>

namespace Bomberman {
    class EventListener;
    
    class EventListenerQueue {
    public:
        virtual ~EventListenerQueue();
        
        void addEventListener(std::shared_ptr<EventListener> eventListener);
        
    protected:
        std::queue<std::shared_ptr<EventListener>> eventListeners;
    };
}

#endif //__EventListenerQueue__hpp__
