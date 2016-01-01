//
//  ScreenComponent.hpp
//  Bomberman
//
//  Created on 31/12/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#ifndef __ScreenComponent__hpp__
#define __ScreenComponent__hpp__

namespace Bomberman {
    class ScreenComponent {
    public:
        ScreenComponent();
        virtual ~ScreenComponent();
        
        bool isEnabled() const;
        void enable();
        void disable();
        
        bool isFinished() const;
        void finish();
        
    private:
        bool enabled;
        bool finished;
    };
}

#endif //__ScreenComponent__hpp__
