//
//  HudLayer.hpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __HudLayer__hpp__
#define __HudLayer__hpp__

#include "../../Core/Drawable.hpp"
#include "../../Core/Texture.hpp"
#include "../../Core/Updatable.hpp"

namespace Bomberman {
    class HudLayer : public Drawable, public Updatable {
    public:
        void draw();
        void update();
        
        void load(std::shared_ptr<SDL_Renderer> renderer);
        
        void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
        
    private:
        Texture hud;
    };
}

#endif //__HudLayer__hpp__
