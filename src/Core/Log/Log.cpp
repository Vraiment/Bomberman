//
//  Log.cpp
//  Bomberman
//
//  Created on 13/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Log.hpp"

#include <iostream>

#include "../Utils/Exception.hpp"
#include "Logger.hpp"
#include "LogLevel.hpp"

using namespace std;

namespace Bomberman {
    Log Log::singleton = Log();
    
    Log::Log() {
        
    }
    
    Log& Log::get() {
        return singleton;
    }
    
    Log& Log::operator<<(int value) {
        buffer << value;
        
        return singleton;
    }
    
    Log& Log::operator<<(long int value) {
        buffer << value;
        
        return singleton;
    }
    
    Log& Log::operator<<(const char *value) {
        buffer << value;
        
        return singleton;
    }
    
    Log& Log::operator<<(string value) {
        buffer << value;
        
        return singleton;
    }
    
    Log& Log::operator<<(void *value) {
        buffer << value;
        
        return singleton;
    }
    
    void Log::operator<<(LogLevel level) {
        flush(level);
        
        if (level == LogLevel::fatal) {
            throw FatalException();
        }
    }
    
    void Log::operator<<(exception exception) {
        flush(LogLevel::fatal);
        
        throw exception;
    }
    
    void Log::addLogger(shared_ptr<Logger> logger) {
        if (!logger) {
            get() << "Adding empty logger." << LogLevel::error;
            return;
        }
        
        if (this->logger) {
            for (auto current = this->logger; true; current = current->next) {
                if (current == logger) {
                    get() << "Adding duplicate logger." << LogLevel::warning;
                    return;
                } else if (!current->next) {
                    current->next = logger;
                    break;
                }
            }
        } else {
            this->logger = logger;
        }
        
        for (auto message : messages) {
            logger->recieveLog(message.first, message.second);
        }
    }
    
    void Log::flush(LogLevel level) {
        string message = buffer.str();
        
        messages.push_back({ message, level });
        for (auto current = logger; current; current = current->next) {
            current->recieveLog(message, level);
        }
        
        buffer.str(string());
        buffer.clear();
    }
}
