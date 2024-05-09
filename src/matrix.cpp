//Implementation for a matrix
#include "matrix.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotInitializedField"
//Constructors/destructors
cppmat::Matrix::Matrix(void){
	x=0;
	y=0;
	rows=nullptr;
}

cppmat::Matrix::Matrix(size_t nx,size_t ny){
	if(!nx || !ny)
		throw cppmat::MatrixDimensionOOBException();
	x=nx;
	y=ny;
	rows=(cppmat::MatrixRow*)calloc(y,sizeof(cppmat::MatrixRow));
	if(!rows)
		throw cppmat::MatrixConstructionException();
	for(size_t i=0;i<this->Y();i++)
		rows[i].build(this->X());
}

cppmat::Matrix::Matrix(const cppmat::Matrix &haystack){
	x=haystack.X();
	y=haystack.Y();
	rows=(cppmat::MatrixRow*)calloc(y,sizeof(cppmat::MatrixRow));
	if(!rows)
		throw cppmat::MatrixConstructionException();
	try{
		for(size_t i=0;i<this->Y();i++){
			rows[i].build(this->X());
			for(size_t j=0;j<this->X();j++)
				rows[i][j]=haystack.Cell(j,i);
		}
	}catch(const cppmat::MatrixBaseException &ex){
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
bool cppmat::Matrix::is_square(void) const noexcept {return x==y;}

//Accessors
float cppmat::Matrix::Cell(size_t sx,size_t sy) const {
	if(sy>y || sx>x)
		throw cppmat::MatrixDimensionOOBException();
	if(x==0 || y==0)
		throw cppmat::MatrixInvalidException();
	return rows[sy].Value(sx);
}

cppmat::MatrixRow cppmat::Matrix::Row(size_t index) const {
	if(index>y)
		throw cppmat::MatrixDimensionOOBException();
	if(x==0 || y==0)
		throw cppmat::MatrixInvalidException();
	return rows[index];
}

cppmat::MatrixRow &cppmat::Matrix::operator[](size_t y_select){
	if(y_select<0 || y_select>y)
		throw cppmat::MatrixDimensionOOBException();
	if(x==0 || y==0)
		throw cppmat::MatrixInvalidException();
	return rows[y_select];
}

cppmat::MatrixRow cppmat::Matrix::column(size_t index) const {
	if(index>this->X())
		throw cppmat::MatrixDimensionOOBException();
	cppmat::MatrixRow ret(this->Y());
	for(size_t row=0;row<this->Y();row++)
		ret[row]=this->Cell(index,row);
	return ret;
}

//Just for unit tests
cppmat::MatrixRow *cppmat::Matrix::Rows(void) const noexcept {
	return rows;
}

//Operators
bool cppmat::Matrix::operator==(const cppmat::Matrix& haystack) const noexcept {
	if(x!=haystack.X() || y!=haystack.Y())
		return false;
	for(size_t yi=0;yi<y;yi++)
		for(size_t xi=0;xi<x;xi++)
			if(this->Cell(xi,yi)!=haystack.Cell(xi,yi))
				return false;
	return true;
}

bool cppmat::Matrix::operator!=(const cppmat::Matrix& haystack) const noexcept {
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
		throw cppmat::MatrixDimensionOOBException();
	cppmat::Matrix ret(*this);
	for(size_t yi=0;yi<ret.Y();yi++)
		for(size_t xi=0;xi<ret.X();xi++)
			ret[yi][xi]+=operant[yi][xi];
	return ret;
}

cppmat::Matrix cppmat::Matrix::operator+=(cppmat::Matrix operant){
	if(this->X() != operant.X() || this->Y() != operant.Y())
		throw cppmat::MatrixDimensionOOBException();
	for(size_t yi=0;yi<this->Y();yi++)
		for(size_t xi=0;xi<this->X();xi++)
			this->operator[](yi)[xi]+=operant[yi][xi];
	return *this;
}

cppmat::Matrix cppmat::Matrix::operator*(float coefficient) const {
	if(this->X()==0 || this->Y()==0)
		throw cppmat::MatrixDimensionOOBException();
	cppmat::Matrix ret(this->X(),this->Y());
	for(size_t ny=0;ny<ret.Y();ny++)
		for(size_t nx=0;nx<ret.X();nx++)
			ret[ny][nx]=coefficient*this->Cell(nx,ny);
	return ret;
}

cppmat::Matrix cppmat::Matrix::operator*=(float coefficient){
	if(this->X()==0 || this->Y()==0)
		throw cppmat::MatrixDimensionOOBException();
	cppmat::Matrix temp(this->X(),this->Y());
	for(size_t ny=0;ny<temp.Y();ny++)
		for(size_t nx=0;nx<temp.X();nx++)
			temp[ny][nx]=coefficient*this->Cell(nx,ny);
	this->operator=(temp);
	return temp;
}

cppmat::Matrix cppmat::Matrix::operator*(const cppmat::Matrix& coefficient) const {
	if(coefficient.X()!=this->Y() || coefficient.Y()!=this->X())
		throw cppmat::MatrixDimensionOOBException();
	cppmat::Matrix ret(this->Y(),coefficient.X());
	for(size_t row=0;row<this->Y();row++){
		for(size_t col=0;col<coefficient.X();col++){
			cppmat::MatrixRow column=coefficient.column(col);
			column=column*this->Row(row);
			float sum=0.0;
			for(size_t i=0;i<column.size();i++)
				sum+=column[i];
			ret[row][col]=sum;
		}
	}
	return ret;
}

cppmat::Matrix cppmat::Matrix::operator*=(cppmat::Matrix coefficient){
	if(coefficient.X()!=this->Y() || coefficient.Y()!=this->X())
		throw cppmat::MatrixDimensionOOBException();
	cppmat::Matrix ret(this->Y(),this->X());
	for(size_t ny=0;ny<ret.Y();ny++)
		for(size_t nx=0;nx<ret.X();nx++)
			ret[ny][nx]=this->Cell(ny,nx)*coefficient.Cell(nx,ny);
	this->operator=(ret);
	return ret;
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
		throw MatrixDimensionOOBException();
	MatrixRow intermediary=rows[first];
	rows[first]=rows[second];
	rows[second]=intermediary;
}

float cppmat::Matrix::determinant(void) const {
	if(this->X()!=this->Y())
		throw cppmat::MatrixDimensionOOBException();
	switch(this->Y()){
		case 0:
		{
			throw cppmat::MatrixDimensionOOBException();
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

cppmat::Matrix cppmat::Matrix::inverse(void) const {
	if(!this->is_square())
		throw cppmat::MatrixDimensionOOBException();
	//this->print();
	switch(this->X()){
        case 0:
		    throw cppmat::MatrixDimensionOOBException();
            break;
        case 1: {
	        cppmat::Matrix ret(1, 1);
	        ret[0][0] = 1 / this->Cell(0, 0);
	        return ret;
	        break;
        }
        case 2: {
	        cppmat::Matrix ret(2, 2);
	        ret[0][0] = this->Cell(1, 1);
	        ret[0][1] = this->Cell(1, 0) * -1;
	        ret[1][0] = this->Cell(0, 1) * -1;
	        ret[1][1] = this->Cell(0, 0);
	        float coefficient = this->Cell(0, 0);
	        coefficient *= this->Cell(1, 1);
	        float coefficient2 = this->Cell(1, 0);
	        coefficient2 *= this->Cell(0, 1);
	        coefficient -= coefficient2;
	        coefficient *= -1;
	        ret *= coefficient;
	        return ret;
			break;
        }
		default: {
			//Create the matrix of minors
			cppmat::Matrix minors(this->X(),this->Y());
			for(size_t ny=0;ny<this->Y();ny++)
				for (size_t nx = 0; nx < this->X(); nx++) {
					cppmat::Matrix temp=cppmat::Matrix::specific_exclude(this,nx,ny);
					//temp.print();
					minors[ny][nx] = temp.determinant();
				}
			//minors.print();
			//Create cofactors
			for(size_t ny=0;ny<minors.Y();ny++)
				for(size_t nx=0;nx<minors.X();nx++)
					minors[ny][nx]*=((ny%2)?(nx%2?1:-1):((nx%2)?-1:1));
			//Transpose
			minors.transpose();
			float det=this->determinant();
			minors*=(1/det);
			return minors;
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
		throw cppmat::MatrixDimensionOOBException();
	if(haystack.X()<=1)
		throw cppmat::MatrixDimensionOOBException();
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

cppmat::Matrix cppmat::Matrix::specific_exclude(const cppmat::Matrix *haystack, size_t ex, size_t ey) {
	if(ex>=haystack->X() || ey>=haystack->Y() || haystack->X()==0 || haystack->Y()==0)
		throw cppmat::MatrixDimensionOOBException();
	cppmat::Matrix ret(haystack->X()-1,haystack->Y()-1);
	//haystack->print();
	for(size_t ny=0;ny<haystack->Y();ny++){
		for(size_t nx=0;nx<haystack->X();nx++){
			if (ny != ey && nx != ex) {
				ret[(ny < ey) ? ny : (ny - 1)][(nx < ex) ? nx : (nx - 1)] = haystack->Cell(nx,ny);
			}
		}
	}
	//ret.print();
	return ret;
}

void cppmat::Matrix::print(void) const noexcept {
	for (size_t ny = 0; ny < this->Y(); ny++) {
		for (size_t nx = 0; nx < this->X(); nx++)
			std::cout<<this->Cell(nx,ny)<<"\t\t";
		std::cout<<std::endl;
	}

}

#pragma clang diagnostic pop