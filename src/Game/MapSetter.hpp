//
//  MapSetter.hpp
//  Bomberman
//
//  Created on 20/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#ifndef __MapSetter__hpp__
#define __MapSetter__hpp__

#include <memory>
#include <string>

namespace Bomberman {
    class CommandFactory;
    class GameLayer;
    class HudLayer;
    
    class MapSetter {
    public:
        bool setMap(std::string fileName);
        
        void setCommandFactory(std::weak_ptr<CommandFactory> commandFactory);
        void setGameLayer(std::weak_ptr<GameLayer> gameLayer);
        void setHudLayer(std::weak_ptr<HudLayer> hudLayer);
        
    private:
        std::weak_ptr<CommandFactory> commandFactory;
        std::weak_ptr<GameLayer> gameLayer;
        std::weak_ptr<HudLayer> hudLayer;
    };
}

#endif //__MapSetter__hpp__
