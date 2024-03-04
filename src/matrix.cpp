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
				rows[i][j]=haystack.Cell(j,i);
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
	if(x==0 || y==0)
		throw cppmat::MatrixInvalidException();
	return rows[sy].Value(sx);
}

cppmat::MatrixRow cppmat::Matrix::Row(size_t index) const {
	if(index<0 || index>y)
		throw cppmat::MatrixDimennsionOOBException();
	if(x==0 || y==0)
		throw cppmat::MatrixInvalidException();
	return rows[index];
}

cppmat::MatrixRow &cppmat::Matrix::operator[](size_t y_select){
	if(y_select<0 || y_select>y)
		throw cppmat::MatrixDimennsionOOBException();
	if(x==0 || y==0)
		throw cppmat::MatrixInvalidException();
	return rows[y_select];
}

//Just for unit tests
cppmat::MatrixRow *cppmat::Matrix::Rows(void) const noexcept {
	return rows;
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
		x=haystack.X();
		y=haystack.Y();
		rows=(cppmat::MatrixRow*)calloc(haystack.Y(),sizeof(cppmat::MatrixRow));
		for(size_t yi=0;yi<haystack.Y();yi++)
			rows[yi]=haystack.Row(yi);
	}catch(cppmat::MatrixBaseException ex){
		throw ex;
	}
	return haystack;
}

cppmat::Matrix cppmat::Matrix::operator+(cppmat::Matrix operant) const {
	if(this->X() != operant.X() || this->Y() != operant.Y())
		throw cppmat::MatrixDimennsionOOBException();
	cppmat::Matrix ret(*this);
	for(size_t yi=0;yi<ret.Y();yi++)
		for(size_t xi=0;xi<ret.X();xi++)
			ret[yi][xi]+=operant[yi][xi];
	return ret;
}

cppmat::Matrix cppmat::Matrix::operator+=(cppmat::Matrix operant){
	if(this->X() != operant.X() || this->Y() != operant.Y())
		throw cppmat::MatrixDimennsionOOBException();
	for(size_t yi=0;yi<this->Y();yi++)
		for(size_t xi=0;xi<this->X();xi++)
			this->operator[](yi)[xi]+=operant[yi][xi];
	return *this;
}

//Operations
cppmat::Matrix cppmat::Matrix::transpose(void) noexcept {
	cppmat::Matrix ret(y,x);
	for(size_t ny=0;ny<this->Y();ny++)
		for(size_t nx=0;nx<this->X();nx++)
			ret[nx][ny]=this->Cell(nx,ny);
	this->operator=(ret);
	return ret;
}

void cppmat::Matrix::swap(size_t first,size_t second){
	if(first<0 || first>=y || second<0 || second>=y)
		throw MatrixDimennsionOOBException();
	MatrixRow intermediary=rows[first];
	rows[first]=rows[second];
	rows[second]=intermediary;
}

//TODO implement unit test
float cppmat::Matrix::determinant(void) const {
	if(this->X()!=this->Y())
		throw cppmat::MatrixDimennsionOOBException();
	switch(this->Y()){
		case 0:
		{
			throw cppmat::MatrixDimennsionOOBException();
			break;
		}
		case 1:
		{
			return this->Cell(0,0);
			break;
		}
		case 2:
		{
			float ret=this->Cell(0,0);
			ret*=this->Cell(1,1);
			float ret2=this->Cell(1,0);
			ret2*=this->Cell(0,1);
			return ret-ret2;
			break;
		}
		default:
		{
			float ret=0;
			for(size_t nx=0;nx<this->X();nx++){
				float placeholder=this->Cell(nx,0);
				cppmat::Matrix recurse(cppmat::Matrix::exclude_column(this,nx));
				placeholder*=recurse.determinant();
				if(nx%2)
					ret-=placeholder;
				else
					ret+=placeholder;
			}
			return ret;
			break;
		}
	}
}

//Identity
cppmat::Matrix cppmat::Matrix::identity(size_t dimension) noexcept {
	cppmat::Matrix ret(dimension,dimension);
	for(size_t y=0;y<dimension;y++)
		for(size_t x=0;x<dimension;x++)
			if(y==x)
				ret[y][x]=1.0;
			else
				ret[y][x]=0.0;
	return ret;
}

//Exclude a column
cppmat::Matrix cppmat::Matrix::exclude_column(const cppmat::Matrix *h,size_t column){
	cppmat::Matrix haystack(*h);
	if(column<0 || column>=haystack.X() || !haystack.Y())
		throw cppmat::MatrixDimennsionOOBException();
	if(haystack.X()<=1)
		throw cppmat::MatrixDimennsionOOBException();
	const size_t row=0;
	cppmat::Matrix ret(haystack.X()-1,haystack.Y()-1);
	for(size_t ny=0;ny<haystack.Y();ny++){
		for(size_t nx=0;nx<haystack.X();nx++){
			if(nx!=column && ny!=row){
				ret[(ny<row)?ny:(ny-1)][(nx<column)?nx:(nx-1)]=haystack[ny][nx];
			}
		}
	}
	return ret;
}
