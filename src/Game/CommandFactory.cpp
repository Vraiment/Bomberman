//
//  CommandFactory.cpp
//  Bomberman
//
//  Created on 16/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "CommandFactory.hpp"

#include "Constants.hpp"
#include "Commands/PlayerCommand.hpp"
#include "Commands/QuitCommand.hpp"
#include "Elements/Player.hpp"
#include "../Core/Log/Log.hpp"
#include "../Core/Log/LogLevel.hpp"
#include "../Core/Utils/Exception.hpp"
#include "../Core/Utils/StringUtils.hpp"

using namespace std;
using namespace Bomberman::Constants;

namespace Bomberman {
    CommandFactory::~CommandFactory() {
        
    }
    
    void CommandFactory::setPlayer(shared_ptr<Player> player) {
        this->player = player;
    }
    
    void CommandFactory::setTileMap(shared_ptr<TileMap> tileMap) {
        this->tileMap = tileMap;
    }
    
    void CommandFactory::setLoopQuiter(shared_ptr<LoopQuiter> loopQuiter) {
        this->loopQuiter = loopQuiter;
    }
    
    shared_ptr<Command> CommandFactory::call(string function, vector<string> arguments) {
        shared_ptr<Command> result;
        
        function = StringUtils::toLower(function);
        for (int n = 0; n < arguments.size(); ++n) {
            arguments[n] = StringUtils::toLower(arguments[n]);
        }
        
        if (FUNC_EXIT == function) {
            result.reset(new QuitCommand(loopQuiter));
        } else {
            throw InvalidFunctionException();
        }
        
        return result;
    }
    
    shared_ptr<Command> CommandFactory::sendMessage(string receiver, string message, vector<string> arguments) {
        shared_ptr<Command> result;
        
        receiver = StringUtils::toLower(receiver);
        message = StringUtils::toLower(message);
        for (int n = 0; n < arguments.size(); ++n) {
            arguments[n] = StringUtils::toLower(arguments[n]);
        }
        
        if (receiver == OBJ_PLAYER) {
            result.reset(new PlayerCommand(player, tileMap, message, arguments));
        } else {
            throw InvalidReceiverException();
        }
        
        return result;
    }
}
