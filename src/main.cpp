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

using namespace Bomberman;
using namespace std;

int main(int argc, char* argv[]) {
    try {
        //Standalone objects
        Engine engine;
        Configuration config("config.xml");
        MainLoop loop;
        
        //Dependants objects
        shared_ptr<Screen> screen(new Screen(config.viewportWidth(), config.viewportHeight(), config.viewportTitle()));
        
        //Game
        loop.addScreen(screen);
        loop.run();
    } catch (exception&) {
        return 1;
    }
    
    return 0;
}
