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
    class SignalSender;
    
    class Console {
    public:
        Console(std::shared_ptr<CommandFactory> commandFactory);
        
        bool visible() const;
        
        void hide();
        void show();
        
        void addToBuffer(char character);
        void addToBuffer(std::string string);
        void removeLastFromBuffer();
        void clearBuffer();
        void commitBuffer();
        
        void setCommandQueue(std::weak_ptr<CommandQueue> commandQueue);
        void setConsoleLayer(std::weak_ptr<ConsoleLayer> consoleLayer);
        void setSignalSender(std::weak_ptr<SignalSender> director);
        
    private:
        static const int BUFFER_SIZE;
        
        bool _visible;
        
        std::string buffer;
        std::weak_ptr<CommandQueue> commandQueue;
        std::weak_ptr<ConsoleLayer> consoleLayer;
        std::weak_ptr<SignalSender> signalSender;
        
        Parser parser;
    };
}

#endif //__Console__hpp__
