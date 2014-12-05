//
//  VectorUtils.hpp
//  Bomberman
//
//  Created on 28/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#ifndef __VectorUtils_hpp__
#define __VectorUtils_hpp__

#include "../Math/Random.hpp"

#include <vector>

namespace Bomberman {
	namespace VectorUtils {
		template <typename T, typename F>
		void removeIf(std::vector<T>& vector, F lambda) {
			for (int n = 0; n < vector.size(); ++n) {
				if (lambda(vector[n])) {
					vector.erase(vector.begin() + n--);
				}
			}
		}
		
		template <typename T>
		T& randomElement(std::vector<T>& vector) {
			return vector[Random::randomInt(static_cast<int>(vector.size()))];
		}
	}
}

#endif // __VectorUtils_hpp__
