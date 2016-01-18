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
    class CommandFactory;
    class CommandQueue;
    class Console;
    
    // Engine stuff
    class LoopQuiter;
    class ScreenManager;
    
    // Event listeners
    class ConsoleEvents;
    class PlayerEvents;
    
    // Layers
    class ConsoleLayer;
    class GameLayer;
    class HowToPlay;
    class HudLayer;
    class LevelListLayer;
    class MainMenuLayer;
    class PauseMenu;
    
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
        void freezeGame();
        void endGame();
        
        void showConsole();
        void hideConsole();
        
        void showPauseMenu();
        void hidePauseMenu();
        
        void showHowToPlay();
        void hideHowToPlay();

        void setLoopQuiter(std::weak_ptr<LoopQuiter> loopQuiter);
        void setScreenManager(std::weak_ptr<ScreenManager> screenManager);
        void setRenderer(std::weak_ptr<SDL_Renderer> renderer);
        
    private:
        enum class ProgramState : std::uint8_t;
        ProgramState state, nextState;
        
        enum class Visibility : std::uint8_t;
        Visibility consoleVisibility;
        Visibility pauseMenuVisibility;
        
        std::weak_ptr<LoopQuiter> loopQuiter;
        std::weak_ptr<ScreenManager> screenManager;
        std::weak_ptr<SDL_Renderer> renderer;
        
        std::weak_ptr<CommandQueue> commandQueue;
        std::weak_ptr<ConsoleEvents> consoleEvents;
        std::weak_ptr<PlayerEvents> playerEvents;
        std::weak_ptr<ConsoleLayer> consoleLayer;
        std::weak_ptr<GameLayer> gameLayer;
        std::weak_ptr<HudLayer> hudLayer;
        std::weak_ptr<MainMenuLayer> mainMenuLayer;
        std::weak_ptr<LevelListLayer> levelListLayer;
        std::weak_ptr<PauseMenu> pauseMenu;
        std::weak_ptr<HowToPlay> howToPlay;
        
        std::shared_ptr<CommandFactory> commandFactory;
        std::shared_ptr<Console> console;
        
        bool _freezeGame;
        bool clearGame;
        std::string nextMap;
        
        void overWriteNextState(ProgramState state);
    };
}

#endif //__Director__hpp__
