//Exceptions for use by cppmat library
#pragma once

#include <exception>
#include <string>

namespace cppmat{

	class MatrixBaseException : std::exception {
	protected:
		std::string message;
	public:
		MatrixBaseException(void);
		virtual const char *what(void) const noexcept;
	};

	class MatrixConstructionException : MatrixBaseException {
	public:
		MatrixConstructionException(void);
		virtual const char *what(void) const noexcept;
		static MatrixConstructionException create(void);
	};

}