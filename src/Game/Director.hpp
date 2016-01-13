//
//  Director.hpp
//  Bomberman
//
//  Created on 11/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#ifndef __Director__hpp__
#define __Director__hpp__

#include "../Core/Updatable.hpp"

#include <cinttypes>
#include <memory>
#include <string>

struct SDL_Renderer;

namespace Bomberman {
    class HudLayer;
    class LoopQuiter;
    class ScreenManager;
    class LevelListLayer;
    
    // Layers
    class MainMenuLayer;
    
    // In game stuff
    class TileMap;
    class Player;
    
    class Director : public Updatable, public std::enable_shared_from_this<Director> {
    public:
        Director();
        
        void load();
        
        void update();
        void postUpdate();
        
        void showLevelList();
        void hideLevelList();
        
        void loadLevel(std::string levelName);

        void setLoopQuiter(std::weak_ptr<LoopQuiter> loopQuiter);
        void setScreenManager(std::weak_ptr<ScreenManager> screenManager);
        void setRenderer(std::weak_ptr<SDL_Renderer> renderer);
        
    private:
        enum class ProgramState : std::uint8_t;
        ProgramState state, nextState;
        
        std::weak_ptr<LoopQuiter> loopQuiter;
        std::weak_ptr<ScreenManager> screenManager;
        std::weak_ptr<SDL_Renderer> renderer;
        
        std::weak_ptr<MainMenuLayer> mainMenuLayer;
        std::weak_ptr<LevelListLayer> levelListLayer;
        
        std::string nextMap;
        
        void overWriteNextState(ProgramState state);
    };
}

#endif //__Director__hpp__
