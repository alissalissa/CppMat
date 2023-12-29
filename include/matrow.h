//Defines a single row of a matrix
#pragma once

#include <assert.h>
#include <cstdlib>
#include <cstring>

#include "matex.h"

namespace cppmat {
    class MatrixRow {
    private:
        float *values;
        size_t n;
    public:
        //Constructors
		MatrixRow(void);
		MatrixRow(size_t);
		MatrixRow(const MatrixRow&);
		~MatrixRow(void);

		//Accessors
		size_t size(void) const;
		float *Values(void) const;
		float Value(size_t) const;

		//operators
		float &operator[](size_t);
		MatrixRow operator+(float) const;
		MatrixRow operator+=(float);
		MatrixRow operator-(float) const;
		MatrixRow operator-=(float);
		MatrixRow operator*(float) const;
		MatrixRow operator*=(float);
		MatrixRow operator=(const MatrixRow&);
    };
}