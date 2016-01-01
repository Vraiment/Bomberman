//
//  Updatable.hpp
//  Bomberman
//
//  Created on 31/12/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __Updatable__hpp__
#define __Updatable__hpp__

#include "ScreenComponent.hpp"

namespace Bomberman {
    class Updatable : public ScreenComponent {
    public:
        virtual void update() = 0;
    };
}

#endif //__Updatable__hpp__
