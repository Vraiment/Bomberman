//
//  HudLayer.hpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __HudLayer__hpp__
#define __HudLayer__hpp__

#include "../Layer.hpp"
#include "../Texture.hpp"

namespace Bomberman {
    class HudLayer : public Layer {
    public:
        void draw();
        void update();
        
        void loadGraphics(std::shared_ptr<SDL_Renderer> renderer);
        
        void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
        
    private:
        Texture hud;
    };
}

#endif //__HudLayer__hpp__
