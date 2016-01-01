//
//  Console.hpp
//  Bomberman
//
//  Created on 15/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __Console__hpp__
#define __Console__hpp__

#include <memory>
#include <string>

#include "Console/Parser.hpp"

namespace Bomberman {
    class CommandFactory;
    class CommandQueue;
    class ConsoleLayer;
    class EventListener;
    class Updatable;
    
    class Console {
    public:
        Console(std::shared_ptr<CommandFactory> commandFactory, std::shared_ptr<CommandQueue> commandQueue, std::shared_ptr<ConsoleLayer> consoleLayer, std::shared_ptr<Updatable> gameLayer, std::shared_ptr<EventListener> playerEvents);
        
        bool visible() const;
        
        void hide();
        void show();
        
        void addToBuffer(char character);
        void addToBuffer(std::string string);
        void removeLastFromBuffer();
        void clearBuffer();
        void commitBuffer();
        
    private:
        static const int BUFFER_SIZE;
        
        std::string buffer;
        std::shared_ptr<CommandQueue> commandQueue;
        std::shared_ptr<EventListener> playerEvents;
        std::shared_ptr<ConsoleLayer> consoleLayer;
        std::shared_ptr<Updatable> gameLayer;
        
        Parser parser;
    };
}

#endif //__Console__hpp__
