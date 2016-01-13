/********************************************************************
 * Micha³ Komorowski
 * 2010-05-16
 * Implementation of a Neighborhood-Based Clustering Algorithm
 ********************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include <sstream>
#include <iostream>
#include <ctime>

#include "Constans.h"
#include "Logger.h"

using namespace std;

namespace NBC
{
	class Timer
	{
	private:
		static bool _enabled;

		double _sum;
		clock_t _startTime;
		clock_t _endTime;

		__declspec(dllexport) double result();
	public:
		__declspec(dllexport) Timer(): _sum(0){}

		__declspec(dllexport) void reset();

		__declspec(dllexport) void start();
		__declspec(dllexport) void end();
		__declspec(dllexport) void end(bool addToSum);

		__declspec(dllexport) void printResult(const char* msg);

		__declspec(dllexport) static void enable();
		__declspec(dllexport) static void disable();
	};
}

#endif