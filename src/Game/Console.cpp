//
//  Console.cpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "Console.hpp"

#include <SDL2/SDL.h>

#include "../Core/CommandQueue.hpp"
#include "../Core/EventListener.hpp"
#include "../Core/Layer.hpp"
#include "Layers/ConsoleLayer.hpp"
#include "../Core/Log/LogSystem.h"

using namespace std;

namespace Bomberman {
    const int Console::BUFFER_SIZE = 80;
    
    Console::Console(shared_ptr<CommandFactory> commandFactory, shared_ptr<CommandQueue> commandQueue, shared_ptr<ConsoleLayer> consoleLayer, shared_ptr<Layer> gameLayer, shared_ptr<EventListener> playerEvents) : parser(commandFactory), commandQueue(commandQueue), consoleLayer(consoleLayer), gameLayer(gameLayer), playerEvents(playerEvents) {
        
    }
    
    bool Console::visible() const {
        return consoleLayer->shouldDraw();
    }
    
    void Console::hide() {
        consoleLayer->shouldDraw(false);
        gameLayer->shouldUpdate(true);
        playerEvents->enable();
        
        SDL_StopTextInput();
    }
    
    void Console::show() {
        consoleLayer->shouldDraw(true);
        gameLayer->shouldUpdate(false);
        playerEvents->disable();
        
        SDL_StartTextInput();
    }
    
    void Console::addToBuffer(char character) {
        buffer += character;
        
        consoleLayer->setInput(buffer);
    }
    
    void Console::addToBuffer(string str) {
        if (buffer.size() < BUFFER_SIZE) {
            buffer += str;
        
            consoleLayer->setInput(buffer);
        }
    }
    
    void Console::removeLastFromBuffer() {
        if (!buffer.empty()) {
            buffer.pop_back();
            
            if (!buffer.empty()) {
                consoleLayer->setInput(buffer);
            } else {
                consoleLayer->clearInput();
            }
        }
    }
    
    void Console::clearBuffer() {
        buffer.clear();
        
        consoleLayer->clearInput();
    }
    
    void Console::commitBuffer() {
        Log::get() << buffer << LogLevel::info;
        auto cmds = parser.parse(buffer);
        
        while (!cmds.empty()) {
            auto cmd = cmds.front();
            commandQueue->addCommand(cmd);
            cmds.pop();
        }
        
        clearBuffer();
    }
}
