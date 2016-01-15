//
//  MainMenuLayer.hpp
//  Bomberman
//
//  Created on 27/12/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __MainMenuLayer__hpp__
#define __MainMenuLayer__hpp__

#include <memory>
#include <vector>

#include "../../Core/EventListener.hpp"
#include "../../Core/Drawable.hpp"
#include "../../Core/Updatable.hpp"

#include "../../Core/Math/Coordinate.hpp"
#include "../../Core/Texture.hpp"

namespace Bomberman {
    class Director;
    class LoopQuiter;
    
    class MainMenuLayer : public EventListener, public Drawable, public Updatable {
    public:
        MainMenuLayer();
        
        void listenEvent(SDL_Event event);
        void update();
        void draw();
        void postUpdate();
        
        void setDirector(std::weak_ptr<Director> Director);
        void setLoopQuiter(std::weak_ptr<LoopQuiter> loopQuiter);
        
        void load(std::shared_ptr<SDL_Renderer> renderer);
        
        void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
        
    private:
        static const int ENTRIES_SPACING;
        
        void select(int entry);
        void select(Coordinate position);
        void pushSelectedButton();
        
        std::vector<Texture *> menuEntries;
        int selectedEntry;
        bool clicking;
        
        bool shouldStartGame, shouldExit;
        Texture startGame;
        Texture exit;
        std::weak_ptr<LoopQuiter> loopQuiter;
        std::weak_ptr<Director> director;
    };
}

#endif //__MainMenuLayer__hpp__
