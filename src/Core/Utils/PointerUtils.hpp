//
//  PointerUtils.hpp
//  Bomberman
//
//  Created on 12/01/16.
//  Copyright (c) 2016 Vraiment. All rights reserved.
//

#ifndef __PointerUtils__hpp__
#define __PointerUtils__hpp__

#include <memory>

namespace Bomberman {
    template <typename T>
    bool lockWeakPointer(std::weak_ptr<T> in, std::shared_ptr<T>& out) {
        if (!in.expired()) {
            out = in.lock();
            return true;
        } else {
            return false;
        }
    }
}

#endif //__PointerUtils__hpp__
