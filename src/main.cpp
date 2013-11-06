//
//  main.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include <SDL2/SDL.h>

#include "Engine.hpp"
#include "MainLoop.hpp"
#include "EmptyScreen.hpp"

using namespace Bomberman;
using namespace std;

int main(int argc, char* argv[]) {
	Engine engine;
	MainLoop loop(engine.getRenderer());
	
	shared_ptr<Screen> emptyScreen(new EmptyScreen());
	loop.addScreen(emptyScreen);
	
	loop.run();
	
	return 0;
}
