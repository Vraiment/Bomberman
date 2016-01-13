//
//  Director.hpp
//  Bomberman
//
//  Created on 11/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#include "Director.hpp"

#include "../Core/LoopQuiter.hpp"
#include "../Core/Log/LogSystem.h"
#include "../Core/ScreenManager.hpp"
#include "../Core/Utils/PointerUtils.hpp"

#include "Layers/MainMenuLayer.hpp"
#include "Layers/LevelListLayer.hpp"

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
        
        // Store everything
        this->mainMenuLayer = mainMenuLayer;
        this->levelListLayer = levelListLayer;
        
        // Register everything
        screenManager->addEventListener(mainMenuLayer);
        screenManager->addEventListener(levelListLayer);
        screenManager->addDrawable(mainMenuLayer);
        screenManager->addDrawable(levelListLayer);
        screenManager->addUpdatable(mainMenuLayer);
        screenManager->addUpdatable(levelListLayer);
        
        // Set the default state for everything
        enableScreenComponent(mainMenuLayer);
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
        
        shared_ptr<MainMenuLayer> mainMenuLayer;
        shared_ptr<LevelListLayer> levelListLayer;
        
        if (!lock<MainMenuLayer>(this->mainMenuLayer, mainMenuLayer, "MainMenuLayer") ||
            !lock<LevelListLayer>(this->levelListLayer, levelListLayer, "LevelListLayer")) {
            return;
        }
        
        if (ProgramState::MainMenu == nextState) {
            enableScreenComponent(mainMenuLayer);
            
            disableScreenComponent(levelListLayer);
        } else if (ProgramState::LevelList == nextState) {
            enableScreenComponent(levelListLayer);
            
            levelListLayer->fillMapList();
            
            disableScreenComponent(mainMenuLayer);
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
