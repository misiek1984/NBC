/********************************************************************
 * Micha³ Komorowski
 * 2010-05-16
 * Implementation of a Neighborhood-Based Clustering Algorithm
 ********************************************************************/

#include "Exceptions.h"

namespace NBC
{
	ostream & operator <<(ostream & os, const NBCException & ex)
	{
		return os << ex.message();
	}

	Logger & operator <<(Logger & logger, const NBCException & ex)
	{
		return logger << ex.message();
	}
}