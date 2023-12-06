//Implementation of a MatrixRow
#include "matrow.h"

//Constructors
cppmat::MatrixRow::MatrixRow(void){
	n=-1;
	values=NULL;
}

cppmat::MatrixRow::MatrixRow(size_t ns){
	if(ns<=0)
		throw cppmat::MatrixDimennsionOOBException::create();
	n=ns;
	values=(float*)calloc(n,sizeof(float));
	if(!values){
		n=-1;
		values=NULL;
		throw cppmat::MatrixConstructionException::create();
	}
	for(size_t i=0;i<n;i++)
		values[i]=0;
}

cppmat::MatrixRow::MatrixRow(const MatrixRow &haystack){
	n=haystack.size();
	values=(float*)calloc(n,sizeof(float));
	if(!values){
		n=-1;
		values=NULL;
		throw cppmat::MatrixConstructionException::create();
	}
	memcpy(values,haystack.Values(),sizeof(float)*n);
}

cppmat::MatrixRow::~MatrixRow(void){
	n=-1;
	free(values);
}

//Accessors
size_t cppmat::MatrixRow::size(void) const {
	return n;
}

float *cppmat::MatrixRow::Values(void) const {
	return values;
}

float cppmat::MatrixRow::Value(size_t index) const {
	if(index<0 || index>=n)
		throw cppmat::MatrixDimennsionOOBException::create();
	assert(values);
	return values[index];
}

//Operators
float &cppmat::MatrixRow::operator[](size_t index){
	if(index<0 || index>=n)
		throw cppmat::MatrixDimennsionOOBException::create();
	assert(values);
	return values[index];
}

cppmat::MatrixRow cppmat::MatrixRow::operator+(float operand) const {
	cppmat::MatrixRow dummy(n);
	for(size_t i=0;i<n;i++)
		dummy[i]=this->Value(i)+operand;
	return dummy;
}

cppmat::MatrixRow cppmat::MatrixRow::operator+=(float operand){
	cppmat::MatrixRow dummy(n);
	for(size_t i=0;i<n;i++)
		dummy[i]=this->Value(i)+operand;
	this->operator=(dummy);
	return dummy;
}

cppmat::MatrixRow cppmat::MatrixRow::operator-(float operand) const {
	cppmat::MatrixRow dummy(n);
	for(size_t i=0;i<n;i++)
		dummy[i]=this->Value(i)-operand;
	return dummy;
}

cppmat::MatrixRow cppmat::MatrixRow::operator-=(float operand){
	cppmat::MatrixRow dummy(n);
	for(size_t i=0;i<n;i++)
		dummy[i]=this->Value(i)-operand;
	this->operator=(dummy);
	return dummy;
}

cppmat::MatrixRow cppmat::MatrixRow::operator=(const cppmat::MatrixRow& haystack){
	n=haystack.size();
	values=(float*)realloc(values,n*sizeof(float));
	if(!values){
		n=-1;
		values=NULL;
		throw cppmat::MatrixConstructionException::create();
	}
	memcpy(values,haystack.Values(),sizeof(float)*n);
	return haystack;
}