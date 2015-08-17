//
//  LoopQuiter.cpp
//  Bomberman
//
//  Created on 17/08/15.
//  Copyright (c) 2015 Vraiment. All rights reserved.
//

#include "LoopQuiter.hpp"

namespace Bomberman {
	LoopQuiter::LoopQuiter() : _quitLoop(false) {
		
	}
	
	LoopQuiter::~LoopQuiter() {
		
	}
	
	bool LoopQuiter::shouldQuit() const {
		return _quitLoop;
	}
	
	void LoopQuiter::quitLoop() {
		_quitLoop = true;
	}
}
