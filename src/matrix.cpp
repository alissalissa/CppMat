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

cppmat::MatrixRow &cppmat::Matrix::operator[](size_t index){
	if(index<0 || index>y)
		throw cppmat::MatrixDimennsionOOBException();
	return rows[index];
}

//Operators
bool cppmat::Matrix::operator==(cppmat::Matrix haystack) const noexcept {
	if(x!=haystack.X() || y!=haystack.Y())
		return false;
	for(size_t yi=0;yi<y;yi++)
		for(size_t xi=0;xi<x;xi++)
			if(this->Cell(xi,yi)!=haystack.Cell(xi,yi))
				return false;
	return true;
}

bool cppmat::Matrix::operator!=(cppmat::Matrix haystack) const noexcept {
	return !this->operator==(haystack);
}

cppmat::Matrix cppmat::Matrix::operator=(const cppmat::Matrix &haystack){
	if(rows)
		free(rows);
	try{
		rows=(cppmat::MatrixRow*)calloc(haystack.Y(),sizeof(cppmat::MatrixRow));
		for(size_t yi=0;yi<haystack.Y();yi++)
			rows[yi]=haystack.Row(yi);
	}catch(cppmat::MatrixBaseException ex){
		throw ex;
	}
	return haystack;
}

//Operations
cppmat::Matrix cppmat::Matrix::transpose(void) noexcept { //TODO unit test
	cppmat::Matrix ret(y,x);
	for(size_t ny=0;ny<this->Y();ny++)
		for(size_t nx=0;nx<this->X();nx++)
			ret[nx][ny]=this->Cell(nx,ny);
	this->operator=(ret);
	return ret;
}

void cppmat::Matrix::swap(size_t first,size_t second){ //TODO unit test
	if(first<0 || first>=y || second<0 || second>=y)
		throw MatrixDimennsionOOBException();
	MatrixRow intermediary=rows[first];
	rows[first]=rows[second];
	rows[second]=intermediary;
}
