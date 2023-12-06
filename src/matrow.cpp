//Implementation of a MatrixRow
#include "matrow.h"

//Constructors
cppmat::MatrixRow::MatrixRow(void){
	n=0;
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