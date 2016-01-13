/********************************************************************
 * Micha³ Komorowski
 * 2010-05-16
 * Implementation of a Neighborhood-Based Clustering Algorithm
 ********************************************************************/

#ifndef INTERFACES_H_
#define INTERFACES_H_

using namespace std;

namespace NBC
{
	template<class T>
	class IIndexable
	{
	public:
		virtual unsigned int size() const = 0;
		virtual T at(unsigned int i) const = 0;
		virtual T operator[](unsigned int i) const = 0;
	};
}

#endif