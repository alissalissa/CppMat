//Class definitions for a simple integer matrix object
#pragma once

#include <cstdlib>

#include "matex.h"

namespace cppmat {
	class matrix{
	private:
		size_t x,y; //0,0 is top left
		int **data;
	public:
		//Constructors
		matrix(void);
		matrix(size_t,size_t);
		matrix(const matrix&);
		~matrix(void);

		//Operations
		matrix multiply(matrix);
		matrix add(matrix);
		int determinant(void);
		matrix transpose(void);

		//Dimensions
		size_t X(void) const;
		size_t Y(void) const;

		//operators
		int *operator[](size_t);
		bool operator==(matrix);
		bool operator!=(matrix);
		bool operator=(const matrix&);
		matrix operator*(matrix);
		matrix operator*=(matrix);
		matrix operator+(matrix);
		matrix operator+=(matrix);
	};
}