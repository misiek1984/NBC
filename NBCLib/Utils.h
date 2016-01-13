#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <string>
#include <sstream>
#include <locale>

using namespace std;

namespace NBC
{
	class Utils
	{
	public:
		template <class T> static __declspec(dllexport)
			bool from_string(T& t, const std::string& s, std::ios_base& (*f)(std::ios_base&))
		{
			std::istringstream iss(s);
			return !(iss >> f >> t).fail();
		}

		template <class T> static __declspec(dllexport) 
			void freeVectorOfVectors(vector< vector< T >* >* vectors)
		{
			for (unsigned int i =0; i < vectors->size(); ++i)
				delete vectors->at(i);

			delete vectors;
		}
	};

	class WithComma: public numpunct<char> // class for decimal numbers with comma
	{
	protected: 
		char do_decimal_point() const { return ','; } // override the function that gives the decimal separator
	};
}

#endif