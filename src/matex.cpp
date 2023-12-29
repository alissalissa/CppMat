//Implementations for cppmat exceptions
#include "matex.h"

//Base exception
cppmat::MatrixBaseException::MatrixBaseException(void) : std::exception() {
	message="Something is wrong somewhere with a matrix object....";
}
const char *cppmat::MatrixBaseException::what(void) const noexcept{
	return message.c_str();
}

//MatrixConstructionException
cppmat::MatrixConstructionException::MatrixConstructionException(void) : cppmat::MatrixBaseException() {
	message="Error encountered while trying to construct a matrix object...";
}
/*cppmat::MatrixConstructionException cppmat::MatrixConstructionException::create(void){
	cppmat::MatrixConstructionException e;
	return e;
}*/

//Matrix dimensions out of bounds
cppmat::MatrixDimennsionOOBException::MatrixDimennsionOOBException(void) : MatrixBaseException() {
	message="The dimensions for this matrix are invalid....";
}
/*cppmat::MatrixDimennsionOOBException cppmat::MatrixDimennsionOOBException::create(void){
	cppmat::MatrixDimennsionOOBException ex;
	return ex;
}*/