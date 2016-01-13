/********************************************************************
 * Micha³ Komorowski
 * 2010-05-16
 * Implementation of a Neighborhood-Based Clustering Algorithm
 ********************************************************************/

#include "Timer.h"

namespace NBC
{
	bool Timer::_enabled = true;

	double Timer::result()
	{
		double diffticks=_endTime-_startTime;
		double diffms=(diffticks*1000)/CLOCKS_PER_SEC; 
		return diffms; 
	}

	void Timer::reset()
	{
		_sum = 0;
	}

	void Timer::start()
	{
		if(_enabled)
		{
			_startTime=clock(); 
		}
	}
	void Timer::end()
	{
		if(_enabled)
		{
			_endTime=clock(); 
		}
	}
	void Timer::end(bool addToSum)
	{
		if(_enabled)
		{
			end();
			_sum += result();
		}
	}

	void Timer::printResult(const char* msg)
	{
		if(_enabled)
			Logger::instance()<<msg<<result()<<" ms "<<NewLine;
	}

	void Timer::enable()
	{
		Timer::_enabled = true;
	}
	void Timer::disable()
	{
		Timer::_enabled = false;
	}
}