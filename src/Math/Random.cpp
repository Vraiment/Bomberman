//
//  Random.cpp
//  Bomberman
//
//  Created on 30/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#include "Random.hpp"

#include <cstdlib>

#define F_RAND_MAX static_cast<float>(RAND_MAX)

namespace Bomberman {
	float frand() {
		return static_cast<float>(rand());
	}
	
	float Random::randomFloat(float max) {
		return randomFloat(0, max);
	}
	
	float Random::randomFloat(float min, float max) {
		return min + (frand() / (F_RAND_MAX / (max - min)));
	}
}
