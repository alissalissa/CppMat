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
			throw cppmat::MatrixConstructionException();
		for(size_t i=0;i<x;i++){
			if(y>0){
				data[i]=(int*)calloc(y,sizeof(int));
				if(!data[i]){
					//We only need to free up to i, since everything has been successful up to this point
					for(size_t j=0;j<i;j++)
						free(data[j]);
					throw cppmat::MatrixConstructionException();
				}
				for(size_t j=0;j<y;j++)
					data[i][j]=0;
			}
		}
	}
}

cppmat::matrix::matrix(const cppmat::matrix &haystack){
	x=haystack.X();
	y=haystack.Y();
	data=(x>0)?(int**)calloc(x,sizeof(int*)):NULL;
	if(!data && x>0)
		throw cppmat::MatrixConstructionException();
	if(x<0 || y<0 || (x==0 && y>0) || (x>0 && y==0))
		throw cppmat::MatrixDimennsionOOBException();
	for(size_t i=0;i<x;i++){
		data[i]=(int*)calloc(y,sizeof(int));
		if(!data){
			for(size_t j=0;j<i;j++)
				free(data[j]);
			free(data);
			throw cppmat::MatrixConstructionException();
		}
		for(size_t j=0;j<y;j++)
			data[i][j]=haystack.cell(i,j);
	}
}

cppmat::matrix::~matrix(void){
	for(size_t i=0;i<x;i++)
		free(data[i]);
	free(data);
}
