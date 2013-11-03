//
//  Matrix.hpp
//  Bomberman
//
//  Created on 30/10/13.
//  Copyright (c) 2013 Vraiment. All rights reserved.
//

#ifndef __Matrix__hpp__
#define __Matrix__hpp__

#include <algorithm>

namespace Bomberman {
	template <class T, class Allocator = std::allocator<T>>
	class Matrix {
	public:
		Matrix() : _columns(0), _rows(0), references(nullptr), values(nullptr) {
			references = new int;
			*references = 1;
		}
		
		Matrix(int size) : _columns(size), _rows(size), references(nullptr), values(nullptr) {
			values = new T[_columns];
			
			for (int i = 0; i < _columns; ++i) {
				values[i] = new T[_rows];
			}
			
			references = new int;
			*references = 1;
		}
		
		Matrix(int columns, int rows) : _columns(columns), _rows(rows), references(nullptr), values(nullptr) {
			values = new T*[_columns];
			
			for (int i = 0; i < _columns; ++i) {
				values[i] = new T[_rows];
			}
			
			references = new int;
			*references = 1;
		}
		
		Matrix(const Matrix& other) : _columns(other._columns), _rows(other._rows), references(other._references), values(other._values) {
			++(*references);
		}
		
		Matrix(Matrix&& other) : _columns(0), _rows(0), references(nullptr), values(nullptr) {
			Matrix::swap(*this, other);
		}
		
		~Matrix() {
			if (references == nullptr) return;
			
			if (--(*references) == 0) {
				for (int i = 0; i < _columns; ++i) {
					delete[] values[i];
				}
				
				delete[] values;
			}
		}
		
		Matrix& operator=(Matrix other) {
			swap(*this, other);
			
			return *this;
		}
		
		int columns() const {
			return _columns;
		}
		
		int rows() const {
			return _rows;
		}
		
		T get(int column, int row) const {
			if (!validPos(column, row)) {
				throw std::out_of_range("matrix");
			}
			
			return values[column][row];
		}
		
		void set(int column, int row, T value) {
			if (!validPos(column, row)) {
				throw std::out_of_range("matrix");
			}
			
			values[column][row] = value;
		}
		
		bool validPos(int column, int row) const {
			return (0 < column) && (column <= _columns) && (0 < row) && (row <= _rows);
		}
		
	private:
		int *references;
		T **values;
		int _columns, _rows;
		
		void swap(Matrix& first, Matrix& second) {
			using std::swap;
			
			swap(first.references, second.references);
			swap(first.values, second.values);
			swap(first._columns, second._columns);
			swap(first._rows, second._rows);
		}
	};
}

#endif //__Matrix__hpp__
