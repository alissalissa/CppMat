//Implementations for cppmat exceptions
#include "matex.h"

//Base exception
cppmat::MatrixBaseException::MatrixBaseException() : std::exception() {
	message="Something is wrong somewhere with a matrix object....";
}
const char *cppmat::MatrixBaseException::what() const noexcept{
	return message.c_str();
}

cppmat::MatrixBaseException::MatrixBaseException(const cppmat::MatrixBaseException &haystack) {
    message=haystack.what();
}

//MatrixConstructionException
cppmat::MatrixConstructionException::MatrixConstructionException() : cppmat::MatrixBaseException() {
	message="Error encountered while trying to construct a matrix object...";
}
/*cppmat::MatrixConstructionException cppmat::MatrixConstructionException::create(void){
	cppmat::MatrixConstructionException e;
	return e;
}*/

//Matrix dimensions out of bounds
cppmat::MatrixDimensionOOBException::MatrixDimensionOOBException() : MatrixBaseException() {
	message="The dimensions for this matrix are invalid....";
}
/*cppmat::MatrixDimensionOOBException cppmat::MatrixDimensionOOBException::create(void){
	cppmat::MatrixDimensionOOBException ex;
	return ex;
}*/

cppmat::MatrixInvalidException::MatrixInvalidException() : cppmat::MatrixBaseException() {
	message="Attempting to manipulate or access an invalid matrix...";
}