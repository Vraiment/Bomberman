//
//  HowToPlay.hpp
//  Bomberman
//
//  Created on 14/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#ifndef __HowToPlay__hpp__
#define __HowToPlay__hpp__

#include "../../Core/Drawable.hpp"
#include "../../Core/EventListener.hpp"
#include "../../Core/Updatable.hpp"

namespace Bomberman {
    class Director;
    
    class HowToPlay : public EventListener, public Drawable, public Updatable {
    public:
        void listenEvent(SDL_Event event);
        void draw();
        void update();
        
        void load(std::shared_ptr<SDL_Renderer> renderer);
        
        void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
        
        void setDirector(std::weak_ptr<Director> director);
        
    private:
        std::weak_ptr<Director> director;
    };
}

#endif //__HowToPlay__hpp__
