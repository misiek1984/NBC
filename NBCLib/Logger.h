/********************************************************************
 * Micha³ Komorowski
 * 2010-05-16
 * Implementation of a Neighborhood-Based Clustering Algorithm
 ********************************************************************/

#ifndef LOGGER_H_
#define LOGGER_H_

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

#include "Constans.h"

using namespace std;

namespace NBC
{
	class Logger
	{
	private:
		bool _writeToConsole;

		const char* _fileName;
		
		vector<string> _buffer;

		static Logger _logger;

		Logger() {}

		~Logger() { flush(); }

		Logger(const Logger& logger) {}

	public:
		__declspec(dllexport) static Logger& instance();

		__declspec(dllexport) Logger & operator <<(const char* msg);

		__declspec(dllexport) Logger & operator <<(const string& msg);

		__declspec(dllexport) Logger & operator <<(double d);

		__declspec(dllexport) void writeHeader();

		__declspec(dllexport) void init(const char* fileName, bool writeToConsole);
	
		__declspec(dllexport) void flush();
	};
}

#endif