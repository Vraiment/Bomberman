//
//  ScreenManager.hpp
//  Bomberman
//
//  Created on 31/12/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __ScreenManager__hpp__
#define __ScreenManager__hpp__

#include <memory>
#include <queue>

namespace Bomberman {
    class EventListener;
    class Drawable;
    class Updatable;
    
    class ScreenManager {
    public:
        virtual ~ScreenManager();
        
        virtual void addEventListener(std::shared_ptr<EventListener> eventListener) = 0;
        virtual void addDrawable(std::shared_ptr<Drawable> drawable) = 0;
        virtual void addUpdatable(std::shared_ptr<Updatable> updatable) = 0;
    };
}

#endif //__ScreenManager__hpp__
