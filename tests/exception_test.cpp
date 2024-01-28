#include <iostream>

#include "matex.h"

bool thrower(void){
	throw cppmat::MatrixConstructionException();
	return true;
}

int main(int argc,char *argv[]){
	try{
		bool success=thrower();
	}catch(cppmat::MatrixBaseException ex){
		std::cout<<ex.what()<<std::endl;
		return 1;
	}
	return 0;
}