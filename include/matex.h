//Exceptions for use by cppmat library
#pragma once

#include <exception>
#include <string>

namespace cppmat{

	class MatrixBaseException : public std::exception {
	protected:
		std::string message;
	public:
		MatrixBaseException();
        MatrixBaseException(const MatrixBaseException&);
		[[nodiscard]] const char *what() const noexcept override;
	};

	class MatrixConstructionException : public MatrixBaseException {
	public:
		MatrixConstructionException();
		//static MatrixConstructionException create(void);
	};

	class MatrixDimensionOOBException : public MatrixBaseException {
	public:
		MatrixDimensionOOBException();
		//static MatrixDimensionOOBException create(void);
	};

	class MatrixInvalidException : public MatrixBaseException {
	public:
		MatrixInvalidException();
	};
}