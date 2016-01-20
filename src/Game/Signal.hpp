//
//  Signal.hpp
//  Bomberman
//
//  Created on 19/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#ifndef __Signal__hpp__
#define __Signal__hpp__

namespace Bomberman {
    enum class Signal {
        ShowConsole,
        InGame,
        PauseGame,
        EndGame,
        HideConsole,
        ShowTutorial,
        LevelList,
        MainMenu
    };
}

#endif //__Signal__hpp__
