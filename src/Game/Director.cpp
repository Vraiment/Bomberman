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

#include "Layers/MainMenuLayer.hpp"

using namespace std;

namespace Bomberman {
    enum class Director::ProgramState : uint8_t {
        None,
        MainMenu,
        LevelListLoad,
        InGame,
        InGamePause,
        MapEditor
    };
    
    Director::Director() : state(ProgramState::None), _showLevelList(false) {
        
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
        
        // Store everything
        this->mainMenuLayer = mainMenuLayer;
        
        // Register everything
        screenManager->addEventListener(mainMenuLayer);
        screenManager->addDrawable(mainMenuLayer);
        screenManager->addUpdatable(mainMenuLayer);
    }
    
    void Director::update() {
        if (ProgramState::None == state) {
            load();
            state = ProgramState::MainMenu;
        }
    }
    
    void Director::postUpdate() {
        
    }
    
    void Director::showLevelList() {
        _showLevelList = true;
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
}
