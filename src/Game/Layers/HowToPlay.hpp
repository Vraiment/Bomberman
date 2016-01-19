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
#include "../../Core/Texture.hpp"
#include "../../Core/Updatable.hpp"

#include <Vector>

struct SDL_Renderer;

namespace Bomberman {
    class Director;
    class Texture;
    
    class HowToPlay : public EventListener, public Drawable, public Updatable {
    public:
        HowToPlay();
        
        void listenEvent(SDL_Event event);
        void draw();
        void update();
        
        void load(std::shared_ptr<SDL_Renderer> renderer);
        
        void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
        
        void setDirector(std::weak_ptr<Director> director);
        
    private:
        void click(Coordinate position);
        void select(Coordinate position);
        
        std::weak_ptr<Director> director;
        
        bool hide;
        enum class Page;
        Page page, nextPage;
        
        Texture mainMenu, instructionsText, items, hud;
        Texture *textRight, *textLeft;
        Texture prev, next;
        std::vector<Texture> instructions;
    };
}

#endif //__HowToPlay__hpp__
