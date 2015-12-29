//
//  EventListener.hpp
//  Bomberman
//
//  Created on 05/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __EventListener__hpp__
#define __EventListener__hpp__

union SDL_Event;

namespace Bomberman {
    class EventListener {
    public:
        EventListener();
        virtual ~EventListener() { }
        
        virtual void listenEvent(SDL_Event event) = 0;
        
        bool enabled() const;
        
        void enable();
        void disable();
        
        bool isZombie() const;
        void isZombie(bool isZombie);
        
    protected:
        bool _isZombie;
        
    private:
        bool _enabled;
    };
}

#endif //__EventListener__hpp__
