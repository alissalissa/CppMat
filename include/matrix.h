//Class definitions for a simple integer matrix object
#pragma once

#include <cstdlib>
#include <iostream> //for debug

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
		float determinant(void) const;
		Matrix transpose(void) noexcept;
		void swap(size_t,size_t);

		//Dimensions
		size_t X(void) const noexcept;
		size_t Y(void) const noexcept;

		//Accessors
		float Cell(size_t,size_t) const;
		MatrixRow Row(size_t) const;
		MatrixRow *Rows(void) const noexcept;

		MatrixRow &operator[](size_t);

		//Operators
		bool operator==(Matrix) const noexcept;
		bool operator!=(Matrix) const noexcept;
		Matrix operator=(const Matrix&);
		Matrix operator*(Matrix) const;
		Matrix operator*=(Matrix);
		Matrix operator+(Matrix) const;
		Matrix operator+=(Matrix);

		//Static
		static Matrix identity(size_t) noexcept;
		static Matrix exclude_column(const cppmat::Matrix*,size_t);
	};
}
