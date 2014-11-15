//
//  Transformer.hpp
//  Bomberman
//
//  Created on 15/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#ifndef __Transformer_hpp__
#define __Transformer_hpp__

#include "Coordinate.hpp"
#include "Matrix.hpp"

#include <stack>

namespace Bomberman {
	class Transformer {
	public:
		Transformer();
		
		Coordinate transform(int i, int j);
		Coordinate transform(Coordinate coordinate);
		
		void translate(int n);
		void translate(int i, int j);
		void translate(Coordinate vector);
		
		void saveState();
		void loadState();
	private:
		Matrix<int> matrix;
		
		std::stack<Matrix<int>> stack;
	};
}

#endif // __Transformer_hpp__
