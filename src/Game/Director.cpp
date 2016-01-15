//
//  Director.hpp
//  Bomberman
//
//  Created on 11/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#include "Director.hpp"

#include "../Core/CommandQueue.hpp"
#include "../Core/Log/LogSystem.h"
#include "../Core/LoopQuiter.hpp"
#include "../Core/ScreenManager.hpp"
#include "../Core/Utils/OperatingSystem.hpp"
#include "../Core/Utils/PointerUtils.hpp"

#include "CommandFactory.hpp"
#include "Console.hpp"
#include "EventListeners/ConsoleEvents.hpp"
#include "EventListeners/PlayerEvents.hpp"
#include "Layers/ConsoleLayer.hpp"
#include "Layers/GameLayer.hpp"
#include "Layers/HudLayer.hpp"
#include "Layers/LevelListLayer.hpp"
#include "Layers/MainMenuLayer.hpp"
#include "Layers/PauseMenu.hpp"
#include "Map/TileMap.hpp"
#include "Map/TileMapBuilder.hpp"
#include "Map/TxtTileMapLoader.hpp"

using namespace std;

namespace Bomberman {
    template <typename T>
    bool _lock(weak_ptr<T> in, shared_ptr<T>& out, string component) {
        bool result = lockWeakPointer(in, out);
        
        if (!result) {
            Log::get() << "No " << component << " for GameStateManager" << LogLevel::error;
        }
        
        return result;
    }
    
    template <typename T>
    void enableScreenComponent(shared_ptr<T> screenComponent) {
        auto eventListener = dynamic_pointer_cast<EventListener>(screenComponent);
        if (eventListener) {
            eventListener->enable();
        }
        
        auto drawable = dynamic_pointer_cast<Drawable>(screenComponent);
        if (drawable) {
            drawable->enable();
        }
        
        auto updatable = dynamic_pointer_cast<Updatable>(screenComponent);
        if (updatable) {
            updatable->enable();
        }
    }
    
    template <typename T>
    void disableScreenComponent(shared_ptr<T> screenComponent) {
        auto eventListener = dynamic_pointer_cast<EventListener>(screenComponent);
        if (eventListener) {
            eventListener->disable();
        }
        
        auto drawable = dynamic_pointer_cast<Drawable>(screenComponent);
        if (drawable) {
            drawable->disable();
        }
        
        auto updatable = dynamic_pointer_cast<Updatable>(screenComponent);
        if (updatable) {
            updatable->disable();
        }
    }
    
    shared_ptr<TileMap> loadTileMap(string mapFile) {
        shared_ptr<TileMap> result;
        string mapPath = getPath({ "maps" }, mapFile);
        
        auto mapLoader = TxtTileMapLoader().load(mapFile);
        
        if (mapLoader) {
            result = make_shared<TileMap>(mapLoader);
        }
        
        return result;
    }
    
    enum class Director::ProgramState : uint8_t {
        None,
        MainMenu,
        LevelList,
        InGame
    };
    
    enum class Director::Visibility : uint8_t {
        None,
        Hide,
        Show
    };
    
    Director::Director() : state(ProgramState::None), nextState(ProgramState::None), consoleVisibility(Visibility::None), pauseMenuVisibility(Visibility::None), _freezeGame(false), clearGame(false) {
        
    }
    
    void Director::load() {
        auto self = shared_from_this();
        shared_ptr<ScreenManager> screenManager;
        shared_ptr<SDL_Renderer> renderer;
        shared_ptr<LoopQuiter> loopQuiter;
        if (!_lock(this->screenManager, screenManager, "ScreenManager") ||
            !_lock(this->renderer, renderer, "Renderer") ||
            !_lock(this->loopQuiter, loopQuiter, "LoopQuiter")) {
            return;
        }
        
        // Initialize main menu
        auto mainMenuLayer = make_shared<MainMenuLayer>();
        mainMenuLayer->setDirector(self);
        mainMenuLayer->setLoopQuiter(loopQuiter);
        mainMenuLayer->load(renderer);
        
        // Initialize map list
        auto levelListLayer = make_shared<LevelListLayer>();
        levelListLayer->load(renderer);
        levelListLayer->setDirector(self);
        
        // Initialize HUD
        auto hudLayer = make_shared<HudLayer>();
        hudLayer->load(renderer);
        
        // Initialize game
        auto gameLayer = make_shared<GameLayer>();
        gameLayer->load(renderer);
        gameLayer->setDirector(self);
        
        // Initialize console layer
        auto consoleLayer = make_shared<ConsoleLayer>();
        consoleLayer->load(renderer);
        Log::get().addLogger(consoleLayer);
        
        // Initialize pause menu
        auto pauseMenu = make_shared<PauseMenu>();
        pauseMenu->load(renderer);
        pauseMenu->setDirector(self);
        pauseMenu->setLoopQuiter(loopQuiter);
        
        // Command stuff
        auto commandQueue = make_shared<CommandQueue>();
        auto commandFactory = make_shared<CommandFactory>();
        commandFactory->setLoopQuiter(loopQuiter);
        
        // Player events
        auto playerEvents = make_shared<PlayerEvents>();
        playerEvents->setCommandFactory(commandFactory);
        playerEvents->setCommandQueue(commandQueue);
        
        // Console
        console = make_shared<Console>(commandFactory);
        console->setCommandQueue(commandQueue);
        console->setConsoleLayer(consoleLayer);
        console->setDirector(self);
        
        // Initialize console events listener
        auto consoleEvents = make_shared<ConsoleEvents>();
        consoleEvents->setConsole(console);
        
        // Store everything
        this->commandFactory = commandFactory;
        this->commandQueue = commandQueue;
        this->gameLayer = gameLayer;
        this->mainMenuLayer = mainMenuLayer;
        this->levelListLayer = levelListLayer;
        this->hudLayer = hudLayer;
        this->consoleLayer = consoleLayer;
        this->consoleEvents = consoleEvents;
        this->playerEvents = playerEvents;
        this->pauseMenu = pauseMenu;
        
        // Register event listeners
        screenManager->addEventListener(mainMenuLayer);
        screenManager->addEventListener(levelListLayer);
        screenManager->addEventListener(consoleEvents);
        screenManager->addEventListener(playerEvents);
        screenManager->addEventListener(pauseMenu);
        screenManager->addEventListener(gameLayer);
        
        // Register drawables
        screenManager->addDrawable(mainMenuLayer);
        screenManager->addDrawable(levelListLayer);
        screenManager->addDrawable(gameLayer);
        screenManager->addDrawable(hudLayer);
        screenManager->addDrawable(consoleLayer);
        screenManager->addDrawable(pauseMenu);
        
        // Register updatables
        screenManager->addUpdatable(gameLayer);
        screenManager->addUpdatable(mainMenuLayer);
        screenManager->addUpdatable(levelListLayer);
        screenManager->addUpdatable(commandQueue);
        screenManager->addUpdatable(pauseMenu);
        
        // Set the default state for everything
        enableScreenComponent(mainMenuLayer);
        disableScreenComponent(commandQueue);
        disableScreenComponent(gameLayer);
        disableScreenComponent(hudLayer);
        disableScreenComponent(levelListLayer);
        disableScreenComponent(consoleEvents);
        disableScreenComponent(playerEvents);
        disableScreenComponent(pauseMenu);
    }
    
    void Director::update() {
        if (ProgramState::None == state) {
            load();
            state = ProgramState::MainMenu;
        }
    }
    
    void Director::postUpdate() {
        shared_ptr<CommandQueue> commandQueue;
        shared_ptr<ConsoleLayer> consoleLayer;
        shared_ptr<GameLayer> gameLayer;
        shared_ptr<HudLayer> hudLayer;
        shared_ptr<MainMenuLayer> mainMenuLayer;
        shared_ptr<LevelListLayer> levelListLayer;
        shared_ptr<ConsoleEvents> consoleEvents;
        shared_ptr<PlayerEvents> playerEvents;
        shared_ptr<PauseMenu> pauseMenu;
        
        if (!_lock(this->mainMenuLayer, mainMenuLayer, "MainMenuLayer") ||
            !_lock(this->levelListLayer, levelListLayer, "LevelListLayer") ||
            !_lock(this->hudLayer, hudLayer, "HudLayer") ||
            !_lock(this->commandQueue, commandQueue, "CommandQueue") ||
            !_lock(this->consoleLayer, consoleLayer, "ConsoleLayer") ||
            !_lock(this->gameLayer, gameLayer, "GameLayer") ||
            !_lock(this->consoleEvents, consoleEvents, "ConsoleEvents") ||
            !_lock(this->playerEvents, playerEvents, "PlayerEvents") ||
            !_lock(this->pauseMenu, pauseMenu, "PauseMenu")) {
            return;
        }
        
        if (ProgramState::MainMenu == nextState) {
            state = ProgramState::MainMenu;
            
            enableScreenComponent(mainMenuLayer);
            
            disableScreenComponent(gameLayer);
            disableScreenComponent(levelListLayer);
            disableScreenComponent(hudLayer);
            disableScreenComponent(commandQueue);
            disableScreenComponent(consoleEvents);
            disableScreenComponent(playerEvents);
            disableScreenComponent(pauseMenu);
        } else if (ProgramState::LevelList == nextState) {
            state = ProgramState::LevelList;
            
            enableScreenComponent(levelListLayer);
            
            levelListLayer->fillMapList();
            
            disableScreenComponent(mainMenuLayer);
            disableScreenComponent(hudLayer);
            disableScreenComponent(commandQueue);
            disableScreenComponent(consoleEvents);
            disableScreenComponent(playerEvents);
            disableScreenComponent(pauseMenu);
        }  else if (ProgramState::InGame == nextState) {
            state = ProgramState::InGame;
            
            auto tileMap = loadTileMap(nextMap);
            
            if (tileMap) {
                enableScreenComponent(hudLayer);
                enableScreenComponent(commandQueue);
                enableScreenComponent(gameLayer);
                enableScreenComponent(consoleLayer);
                enableScreenComponent(consoleEvents);
                enableScreenComponent(playerEvents);
                
                // set up the tileMap and the player for anything that require them
                commandFactory->setTileMap(tileMap);
                commandFactory->setPlayer(tileMap->player());
                gameLayer->setTileMap(tileMap);
                hudLayer->setTileMap(tileMap);
                hudLayer->setPlayer(tileMap->player());
                // Only the event listener of the pause menu should be active
                pauseMenu->hide();
                pauseMenu->EventListener::enable();
                // Disable console drawing
                consoleLayer->Drawable::disable();
                
                disableScreenComponent(mainMenuLayer);
                disableScreenComponent(levelListLayer);
            } else {
                Log::get() << "Could not open map \"" << nextMap << "\"" << LogLevel::error;
            }
        }
        
        if (clearGame) {
            commandQueue->clear();
            gameLayer->setTileMap(nullptr);
            
            clearGame = false;
        }
        
        if (_freezeGame) {
            commandQueue->disable();
            consoleEvents->disable();
            playerEvents->disable();
            gameLayer->Updatable::disable();
            disableScreenComponent(consoleLayer);
            disableScreenComponent(pauseMenu);

            _freezeGame = false;
        }

        if (Visibility::Hide == consoleVisibility) {
            disableScreenComponent(consoleLayer);
            
            gameLayer->Updatable::enable();
            playerEvents->enable();
            pauseMenu->EventListener::enable();
            
            consoleVisibility = Visibility::None;
        } else if (Visibility::Show == consoleVisibility) {
            gameLayer->Updatable::disable();
            playerEvents->disable();
            pauseMenu->EventListener::disable();
            
            enableScreenComponent(consoleLayer);
            
            consoleVisibility = Visibility::None;
        }
        
        if (Visibility::Hide == pauseMenuVisibility) {
            pauseMenu->hide();
            
            gameLayer->Updatable::enable();
            consoleEvents->enable();
            playerEvents->enable();
            commandQueue->enable();
            
            pauseMenuVisibility = Visibility::None;
        } else if (Visibility::Show == pauseMenuVisibility) {
            gameLayer->Updatable::disable();
            consoleEvents->disable();
            playerEvents->disable();
            commandQueue->disable();
            
            pauseMenu->show();
            
            pauseMenuVisibility = Visibility::None;
        }
        
        nextState = ProgramState::None;
    }
    
    void Director::hideLevelList() {
        overWriteNextState(ProgramState::MainMenu);
    }
    
    void Director::showLevelList() {
        overWriteNextState(ProgramState::LevelList);
    }
    
    void Director::loadLevel(string levelName) {
        overWriteNextState(ProgramState::InGame);
        
        nextMap = levelName;
    }
    
    void Director::freezeGame() {
        _freezeGame = true;
    }

    void Director::endGame() {
        overWriteNextState(ProgramState::MainMenu);
        
        clearGame = true;
    }
    
    void Director::showConsole() {
        consoleVisibility = Visibility::Show;
    }
    
    void Director::hideConsole() {
        consoleVisibility = Visibility::Hide;
    }
    
    void Director::showPauseMenu() {
        pauseMenuVisibility = Visibility::Show;
    }
    
    void Director::hidePauseMenu() {
        pauseMenuVisibility = Visibility::Hide;
    }
    
    void Director::setLoopQuiter(weak_ptr<LoopQuiter> loopQuiter) {
        this->loopQuiter = loopQuiter;
    }
    
    void Director::setScreenManager(weak_ptr<ScreenManager> screenManager) {
        this->screenManager = screenManager;
    }
    
    void Director::setRenderer(weak_ptr<SDL_Renderer> renderer) {
        this->renderer = renderer;
    }
    
    void Director::overWriteNextState(ProgramState state) {
        if (ProgramState::None != nextState) {
            Log::get() << "Overwriting next state: " << static_cast<int>(nextState) << LogLevel::warning;
        }
        
        nextState = state;
    }
}
