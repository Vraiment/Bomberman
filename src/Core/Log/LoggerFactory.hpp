//
//  LoggerFactory.hpp
//  Bomberman
//
//  Created on 06/12/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#ifndef __LoggerFactory_hpp__
#define __LoggerFactory_hpp__

#include <memory>
#include <string>

namespace Bomberman {
    class Logger;
    
    class LoggerFactory {
    public:
        static LoggerFactory& get();
        
        std::shared_ptr<Logger> getLogger(std::string loggerName);
        
    private:
        LoggerFactory();
        
        struct {
            std::shared_ptr<Logger> stdOut;
        } loggers;
        
        static LoggerFactory singleton;
    };
}

#endif // __LoggerFactory_hpp__
