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
#include "Layers/ConsoleLayer.hpp"
#include "Layers/GameLayer.hpp"
#include "Layers/HudLayer.hpp"
#include "Layers/LevelListLayer.hpp"
#include "Layers/MainMenuLayer.hpp"
#include "Map/TileMap.hpp"
#include "Map/TileMapBuilder.hpp"
#include "Map/TxtTileMapLoader.hpp"

using namespace std;

namespace Bomberman {
    template <typename T>
    bool lock(weak_ptr<T> in, shared_ptr<T>& out, string component) {
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
    
    Director::Director() : state(ProgramState::None), nextState(ProgramState::None) {
        
    }
    
    void Director::load() {
        if (this->screenManager.expired()) {
            Log::get() << "No ScreenManager for GameStateManager" << LogLevel::error;
            return;
        } else if (this->renderer.expired()) {
            Log::get() << "No Renderer for GameStateManager" << LogLevel::error;
            return;
        }
        auto self = shared_from_this();
        auto screenManager = this->screenManager.lock();
        auto renderer = this->renderer.lock();
        
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
        
        // Initialize console layer
        auto consoleLayer = make_shared<ConsoleLayer>();
        consoleLayer->load(renderer);
        
        // Command stuff
        auto commandQueue = make_shared<CommandQueue>();
        auto commandFactory = make_shared<CommandFactory>();
        
        // Console
        console = make_shared<Console>(commandFactory);
        console->setCommandQueue(commandQueue);
        console->setConsoleLayer(consoleLayer);
        console->setDirector(self);
        
        // Store everything
        this->commandFactory = commandFactory;
        this->commandQueue = commandQueue;
        this->gameLayer = gameLayer;
        this->mainMenuLayer = mainMenuLayer;
        this->levelListLayer = levelListLayer;
        this->hudLayer = hudLayer;
        this->consoleLayer = consoleLayer;
        
        // Register event listeners
        screenManager->addEventListener(mainMenuLayer);
        screenManager->addEventListener(levelListLayer);
        
        // Register drawables
        screenManager->addDrawable(mainMenuLayer);
        screenManager->addDrawable(levelListLayer);
        screenManager->addDrawable(gameLayer);
        screenManager->addDrawable(hudLayer);
        screenManager->addDrawable(consoleLayer);
        
        // Register updatables
        screenManager->addUpdatable(gameLayer);
        screenManager->addUpdatable(mainMenuLayer);
        screenManager->addUpdatable(levelListLayer);
        screenManager->addUpdatable(commandQueue);
        
        // Set the default state for everything
        enableScreenComponent(mainMenuLayer);
        disableScreenComponent(commandQueue);
        disableScreenComponent(gameLayer);
        disableScreenComponent(hudLayer);
        disableScreenComponent(levelListLayer);
    }
    
    void Director::update() {
        if (ProgramState::None == state) {
            load();
            state = ProgramState::MainMenu;
        }
    }
    
    void Director::postUpdate() {
        if (ProgramState::None == nextState) {
            return;
        }
        
        shared_ptr<CommandQueue> commandQueue;
        shared_ptr<ConsoleLayer> consoleLayer;
        shared_ptr<GameLayer> gameLayer;
        shared_ptr<HudLayer> hudLayer;
        shared_ptr<MainMenuLayer> mainMenuLayer;
        shared_ptr<LevelListLayer> levelListLayer;
        
        if (!lock<MainMenuLayer>(this->mainMenuLayer, mainMenuLayer, "MainMenuLayer") ||
            !lock<LevelListLayer>(this->levelListLayer, levelListLayer, "LevelListLayer") ||
            !lock<HudLayer>(this->hudLayer, hudLayer, "HudLayer") ||
            !lock<CommandQueue>(this->commandQueue, commandQueue, "CommandQueue") ||
            !lock<ConsoleLayer>(this->consoleLayer, consoleLayer, "ConsoleLayer") ||
            !lock<GameLayer>(this->gameLayer, gameLayer, "GameLayer")) {
            return;
        }
        
        if (ProgramState::MainMenu == nextState) {
            enableScreenComponent(mainMenuLayer);
            
            disableScreenComponent(levelListLayer);
            disableScreenComponent(hudLayer);
            disableScreenComponent(commandQueue);
        } else if (ProgramState::LevelList == nextState) {
            enableScreenComponent(levelListLayer);
            
            levelListLayer->fillMapList();
            
            disableScreenComponent(mainMenuLayer);
            disableScreenComponent(hudLayer);
            disableScreenComponent(commandQueue);
        }  else if (ProgramState::InGame == nextState) {
            auto tileMap = loadTileMap(nextMap);
            
            if (tileMap) {
                enableScreenComponent(hudLayer);
                enableScreenComponent(commandQueue);
                enableScreenComponent(gameLayer);
                enableScreenComponent(consoleLayer);
                
                commandQueue->clear();
                gameLayer->setTileMap(tileMap);
                hudLayer->setTileMap(tileMap);
                hudLayer->setPlayer(tileMap->player());
                consoleLayer->Drawable::disable();
                
                disableScreenComponent(mainMenuLayer);
                disableScreenComponent(levelListLayer);
            } else {
                Log::get() << "Could not open map \"" << nextMap << "\"" << LogLevel::error;
            }
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
    
    void Director::pauseGame() {
        if (ProgramState::InGame != state) {
            Log::get() << "Not in game, cannot pause game" << LogLevel::error;
            return;
        }
    }
    
    void Director::unPauseGame() {
        if (ProgramState::InGame != state) {
            Log::get() << "Not in game, cannot pause game" << LogLevel::error;
            return;
        }
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
