//
//  Transformer.cpp
//  Bomberman
//
//  Created on 15/11/14.
//  Copyright (c) 2014 Vraiment. All rights reserved.
//

#include "Transformer.hpp"

namespace Bomberman {
	Matrix<int> identity(int size) {
		auto result = Matrix<int>(size);
		
		result.reset(0);
		
		for (int n = 0; n < size; ++n) {
			result.pos(n, n) = 1;
		}
		
		return result;
	}
	
	Transformer::Transformer() : matrix(identity(3)) {
		
	}
	
	Coordinate Transformer::transform(int i, int j) {
		Matrix<int> input(3, 1);
		Matrix<int> transformed(3);
		
		input.pos(0, 0) = i;
		input.pos(1, 0) = j;
		input.pos(2, 0) = 1;
		transformed.reset(0);
		
		Matrix<int>::multiply(matrix, input, transformed);

		Coordinate result;
		result.i = transformed.pos(0, 0);
		result.j = transformed.pos(1, 0);
		return result;
	}
	
	Coordinate Transformer::transform(Coordinate coordinate) {
		return transform(coordinate.i, coordinate.j);
	}
	
	void Transformer::translate(int n) {
		translate(n, n);
	}
	
	void Transformer::translate(int i, int j) {
		Matrix<int> result(3);
		Matrix<int> translation = identity(3);
		
		result.reset(0);
		translation.pos(0, 2) = i;
		translation.pos(1, 2) = j;
		
		Matrix<int>::multiply(matrix, translation, result);
		
		matrix = result;
	}
	
	void Transformer::translate(Coordinate vector) {
		translate(vector.i, vector.j);
	}
	
	void Transformer::saveState() {
		stack.push(matrix);
	}
	
	void Transformer::loadState() {
		matrix = stack.top();
		stack.pop();
	}
}
