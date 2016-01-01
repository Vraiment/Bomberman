//
//  Drawable.hpp
//  Bomberman
//
//  Created on 31/12/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __Drawable__hpp__
#define __Drawable__hpp__

#include "ScreenComponent.hpp"

#include <memory>

struct SDL_Renderer;

namespace Bomberman {
    class Rectangle;
    
    class Drawable : public ScreenComponent {
    public:
        virtual void draw() = 0;
        
        virtual void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
    };
}

#endif //__Drawable__hpp__
