//Implementation for a matrix
#include "matrix.h"

//Constructors/destructors
cppmat::Matrix::Matrix(void){
	x=0;
	y=0;
	rows=NULL;
}

cppmat::Matrix::Matrix(size_t nx,size_t ny){
	if(nx<0 || ny<0)
		throw cppmat::MatrixDimennsionOOBException();
	x=nx;
	y=ny;
	rows=(cppmat::MatrixRow*)calloc(y,sizeof(cppmat::MatrixRow));
	if(!rows)
		throw cppmat::MatrixConstructionException();
	for(size_t i=0;i<y;i++)
		rows[i].build(x);
}

cppmat::Matrix::Matrix(const cppmat::Matrix &haystack){
	x=haystack.X();
	y=haystack.Y();
	rows=(cppmat::MatrixRow*)calloc(y,sizeof(cppmat::MatrixRow));
	if(!rows)
		throw cppmat::MatrixConstructionException();
	try{
		for(size_t i=0;i<y;i++){
			rows[i].build(x);
			for(size_t j=0;j<x;j++)
				rows[i][j]=haystack.Cell(i,j);
		}
	}catch(cppmat::MatrixBaseException ex){
		throw ex;
	}
}

cppmat::Matrix::~Matrix(void){
	if(rows)
		free(rows);
}

//Dimensions
size_t cppmat::Matrix::X(void) const noexcept {return x;}
size_t cppmat::Matrix::Y(void) const noexcept {return y;}

//Accessors
float cppmat::Matrix::Cell(size_t sx,size_t sy) const {
	if(sy<0 || sy>y || sx<0 || sx>x)
		throw cppmat::MatrixDimennsionOOBException();
	return rows[sy].Value(sx);
}

cppmat::MatrixRow cppmat::Matrix::Row(size_t index) const {
	if(index<0 || index>y)
		throw cppmat::MatrixDimennsionOOBException();
	return rows[index];
}
