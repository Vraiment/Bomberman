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

#include "../../Core/Drawable.hpp"
#include "../../Core/Updatable.hpp"

#include "../../Core/Math/Coordinate.hpp"
#include "../../Core/Texture.hpp"

namespace Bomberman {
    class LoopQuiter;
    class ScreenManager;
    
    class MainMenuLayer : public Drawable, public Updatable, public std::enable_shared_from_this<MainMenuLayer> {
    public:
        MainMenuLayer();
        
        void update();
        void draw();
        
        void select(Coordinate position);
        void click(Coordinate position);
        
        void setScreenManager(std::shared_ptr<ScreenManager> screenManager);
        void setLoopQuiter(std::shared_ptr<LoopQuiter> loopQuiter);
        
        void load(std::shared_ptr<SDL_Renderer> renderer);
        
        void screenSizeChanged(Rectangle previousSize, Rectangle newSize);
        
    private:
        static const int ENTRIES_SPACING;
        
        bool shouldStartGame, shouldExit;
        Texture *selected;
        Texture startGame;
        Texture exit;
        std::shared_ptr<LoopQuiter> loopQuiter;
        std::shared_ptr<SDL_Renderer> renderer;
        std::shared_ptr<ScreenManager> screenManager;
    };
}

#endif //__MainMenuLayer__hpp__
