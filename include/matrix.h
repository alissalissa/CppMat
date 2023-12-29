//Class definitions for a simple integer matrix object
#pragma once

#include <cstdlib>

#include "matex.h"
#include "matrow.h"

namespace cppmat {
	class Matrix{
	private:
		size_t x,y; //0,0 is top left
		MatrixRow *rows;
	public:
		//Constructors
		Matrix(void);
		Matrix(size_t,size_t);
		Matrix(const Matrix&);
		~Matrix(void);

		//Operations
		Matrix multiply(Matrix);
		Matrix add(Matrix);
		int determinant(void);
		Matrix transpose(void);

		//Dimensions
		size_t X(void) const;
		size_t Y(void) const;

		//Accessors
		int cell(size_t,size_t) const;
		MatrixRow get_row(size_t) const;

		//operators
		MatrixRow &operator[](size_t);
		bool operator==(Matrix);
		bool operator!=(Matrix);
		bool operator=(const Matrix&);
		Matrix operator*(Matrix);
		Matrix operator*=(Matrix);
		Matrix operator+(Matrix);
		Matrix operator+=(Matrix);
	};
}