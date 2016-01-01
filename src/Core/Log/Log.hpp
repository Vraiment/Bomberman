//
//  Log.hpp
//  Bomberman
//
//  Created on 13/11/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Log__hpp__
#define __Log__hpp__

#include <memory>
#include <sstream>
#include <vector>

#include "LogLevel.hpp"

namespace Bomberman {
    class Logger;
    
    class Log {
    public:
        static Log& get();
        
        Log& operator<<(int value);
        Log& operator<<(long int value);
        Log& operator<<(const char *value);
        Log& operator<<(std::string value);
        Log& operator<<(void *value);
        void operator<<(LogLevel level);
        void operator<<(std::exception exception);
        
        void addLogger(std::shared_ptr<Logger> logger);
        
    private:
        Log();
        
        void flush(LogLevel level);
        
        std::stringstream buffer;
        std::vector<std::pair<std::string, LogLevel>> messages;
        std::shared_ptr<Logger> logger;
        
        static Log singleton;
    };
}

#endif //__Log__hpp__
