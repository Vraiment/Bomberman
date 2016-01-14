//
//  main.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include <memory>

#include "Core/Engine.hpp"
#include "Core/MainLoop.hpp"
#include "Core/Screen.hpp"
#include "Core/ScreenManager.hpp"

#include "Game/Configuration.hpp"
#include "Game/Director.hpp"

using namespace Bomberman;
using namespace std;

int main(int argc, char* argv[]) {
    try {
        //Standalone objects
        Engine engine;
        Configuration config("config.xml");
        MainLoop loop;
        auto director = make_shared<Director>();
        
        //Dependants objects
        shared_ptr<Screen> screen(new Screen(config.viewportWidth(), config.viewportHeight(), config.viewportTitle()));
        
        // Configure the director
        director->setScreenManager(screen->getScreenManager());
        director->setLoopQuiter(loop.quiter());
        director->setRenderer(screen->renderer());
        
        // Register the director
        screen->getScreenManager()->addUpdatable(director);
        
        //Game
        loop.addScreen(screen);
        loop.run();
    } catch (exception&) {
        return 1;
    }
    
    return 0;
}
