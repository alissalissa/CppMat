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
		Matrix inverse(void) const;

		//debug
		void print(void) const noexcept;

		//Dimensions
		size_t X(void) const noexcept;
		size_t Y(void) const noexcept;
		bool is_square(void) const noexcept;

		//Accessors
		float Cell(size_t,size_t) const;
		MatrixRow Row(size_t) const;
		MatrixRow *Rows(void) const noexcept;

		MatrixRow &operator[](size_t);

		//Operators
		bool operator==(const Matrix&) const noexcept;
		bool operator!=(const Matrix&) const noexcept;
		Matrix operator=(const Matrix&);
		Matrix operator*(Matrix) const;
		Matrix operator*=(Matrix);
		Matrix operator*(float) const;
		Matrix operator*=(float);
		Matrix operator+(Matrix) const;
		Matrix operator+=(Matrix);

		//Static
		static Matrix identity(size_t) noexcept;
		static Matrix exclude_column(const cppmat::Matrix*,size_t);
		static Matrix specific_exclude(const cppmat::Matrix*,size_t,size_t);
	};
}
