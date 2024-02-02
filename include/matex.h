//Exceptions for use by cppmat library
#pragma once

#include <exception>
#include <string>

namespace cppmat{

	class MatrixBaseException : public std::exception {
	protected:
		std::string message;
	public:
		MatrixBaseException(void);
		const char *what(void) const noexcept;
	};

	class MatrixConstructionException : public MatrixBaseException {
	public:
		MatrixConstructionException(void);
		//static MatrixConstructionException create(void);
	};

	class MatrixDimennsionOOBException : public MatrixBaseException {
	public:
		MatrixDimennsionOOBException(void);
		//static MatrixDimennsionOOBException create(void);
	};

	class MatrixInvalidException : public MatrixBaseException {
	public:
		MatrixInvalidException(void);
	};
}