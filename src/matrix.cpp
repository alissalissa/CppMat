//Implementation for a matrix
#include "matrix.h"

//Constructors/destructors
cppmat::matrix::matrix(void){
	x=0;
	y=0;
	data=NULL;
}

cppmat::matrix::matrix(size_t nx,size_t ny){
	x=nx;
	y=ny;
	if(x>0){
		data=(int**)calloc(x,sizeof(int*));
		if(!data)
			throw cppmat::MatrixConstructionException::create();
		for(int i=0;i<x;i++)
			data[i]=(y>0)?(int*)calloc(y,sizeof(int)):NULL;
	}
}

cppmat::matrix::matrix(const cppmat::matrix &haystack){
	x=haystack.X();
	y=haystack.Y();
	//TODO finish this
	data=(int**)calloc(x,sizeof(int*));
	if(!data)
		throw cppmat::MatrixConstructionException::create();
}
