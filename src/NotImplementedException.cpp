//
//  NotImplementedException.cpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "NotImplementedException.hpp"

namespace Bomberman {
	const char* NotImplementedException::what() const noexcept {
		return "operation not implemented";
	}
}
