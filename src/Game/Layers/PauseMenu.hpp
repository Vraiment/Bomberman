//
//  PauseMenu.hpp
//  Bomberman
//
//  Created on 13/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#ifndef __PauseMenu__hpp__
#define __PauseMenu__hpp__

#include "../../Core/Drawable.hpp"
#include "../../Core/EventListener.hpp"
#include "../../Core/Texture.hpp"
#include "../../Core/Updatable.hpp"

struct SDL_Renderer;

namespace Bomberman {
    class Director;
    class LoopQuiter;
    
    class PauseMenu : public EventListener, public Drawable, public Updatable {
    public:
        PauseMenu();
        
        void listenEvent(SDL_Event event);
        void draw();
        void update();
        
        void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
        
        void load(std::shared_ptr<SDL_Renderer> renderer);
        
        void setDirector(std::weak_ptr<Director> director);
        void setLoopQuiter(std::weak_ptr<LoopQuiter> loopQuitter);
        
        void show();
        void hide();
        
    private:
        void pushSelectedButton();
        void select(Coordinate position);
        
        std::weak_ptr<Director> director;
        std::weak_ptr<LoopQuiter> loopQuiter;
        
        int selected;
        bool clicking;
        
        Texture background;
        Texture continueGame;
        Texture quitToMainMenu;
        Texture quitToDesktop;
    };
}

#endif //__PauseMenu__hpp__
