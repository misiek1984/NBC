/********************************************************************
 * Micha³ Komorowski
 * 2010-05-16
 * Implementation of a Neighborhood-Based Clustering Algorithm
 ********************************************************************/

#include "Logger.h"

namespace NBC
{
	Logger Logger::_logger;

	Logger& Logger::instance()
	{
		return _logger;
	}

	void Logger::init(const char* fileName, bool writeToConsole)
	{
		_writeToConsole = writeToConsole;
		_fileName = fileName;
	}

	Logger & Logger::operator <<(const char* msg)
	{
		return _logger<<string(msg);
	}

	Logger& Logger::operator <<(const string& msg)
	{
		if(_writeToConsole)
			cout<<msg.c_str();

		_buffer.push_back(msg);

		if(_buffer.size() > 20)
			flush();

		return _logger;
	}

	Logger& Logger::operator <<(double d)
	{
		ostringstream ss;
		ss<<d;
		return _logger<<ss.str();
	}

	void Logger::writeHeader()
	{

		time_t rawtime;
		struct tm * timeinfo;
		char buffer [80];

		time (&rawtime);
		timeinfo = localtime(&rawtime);

		strftime (buffer,80,"**************** %d-%m-%Y %H:%M ****************",timeinfo);

		_logger<<buffer<<NewLine;
	}

	void Logger::flush()
	{
		if(_fileName != NULL)
		{
			ofstream fout(_fileName, ios_base::app);
			if(fout.is_open())
			{
				for(int i = 0; i < _buffer.size(); ++i)
					fout<<_buffer.at(i).c_str();

				_buffer.clear();
				fout.close();
			}
		}
	}
}