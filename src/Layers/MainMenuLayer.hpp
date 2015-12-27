//
//  MainMenuLayer.hpp
//  Bomberman
//
//  Created on 27/12/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __MainMenuLayer__hpp__
#define __MainMenuLayer__hpp__

#include "../Layer.hpp"

#include "../Texture.hpp"

namespace Bomberman {
    class MainMenuLayer : public Layer {
    public:
        MainMenuLayer();
        
        void update();
        void draw();
        
        void select(Coordinate position);
        
        void click(Coordinate position);
        
        void load(std::shared_ptr<SDL_Renderer> renderer);
        
        void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
        
    private:
        static const int ENTRIES_SPACING;
        
        Texture *selected;
        Texture startGame;
        Texture exit;
    };
}

#endif //__MainMenuLayer__hpp__
