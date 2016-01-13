/********************************************************************
 * Micha³ Komorowski
 * 2010-05-16
 * Implementation of a Neighborhood-Based Clustering Algorithm
 ********************************************************************/

#ifndef NBC_EXCEPTION_H_
#define NBC_EXCEPTION_H_

#include <string>
#include <sstream>
#include <iostream>
#include <exception>

#include "Logger.h"

using namespace std;

namespace NBC
{
	// <summary>
	// The base class for exceptions used in the library
	// </summary>
	class NBCException
	{
	protected:
		string _msg;

	public:
		__declspec(dllexport) NBCException(const string& msg)
		{
			_msg = msg;
		}

		__declspec(dllexport) NBCException()
		{}

		__declspec(dllexport) const string& message() const
		{
			return _msg;
		}

		__declspec(dllexport) friend ostream & operator <<(ostream & os, const NBCException & ex);

		__declspec(dllexport) friend Logger & operator <<(Logger & logger, const NBCException & ex);
	};

	// <summary>
	// The exception that is thrown when unexpected char is found in the file
	// </summary>
	class UnexpectedCharException: 
		public NBCException
	{
	public:
		__declspec(dllexport) UnexpectedCharException(int lines, int columns)
		{
			ostringstream ss;

			ss << "Unexpected sign in line ";
			ss << lines;
			ss << " column ";
			ss << columns;
			_msg = ss.str();
		}
	};

	// <summary>
	// The exception that is thrown when not all vectors have the same length
	// </summary>
	class AllVectorsShouldHaveTheSameLengthException: 
		public NBCException
	{
	public:
		__declspec(dllexport) AllVectorsShouldHaveTheSameLengthException()
		{
			_msg = "All vectors should have the same length!";
		}
	};
}

#endif