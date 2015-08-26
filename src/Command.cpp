//
//  Command.cpp
//  Bomberman
//
//  Created on 10/12/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#include "Command.hpp"

namespace Bomberman {
	Command::Command() : _finished(false) {
	}
	
	Command::~Command() {
		
	}
	
	bool Command::finished() const {
		return _finished;
	}
}
