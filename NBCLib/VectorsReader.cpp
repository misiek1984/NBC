/********************************************************************
 * Micha³ Komorowski
 * 2010-05-16
 * Implementation of a Neighborhood-Based Clustering Algorithm
 ********************************************************************/

#include "VectorsReader.h"

namespace NBC
{
	//*****************************************************************
	//PRIVATE METHODS
	//*****************************************************************

	void VectorsReader::freeMemory()
	{
		if(_vectors != NULL)
		{
			Utils::freeVectorOfVectors(_vectors);
			_vectors = NULL;
		}

		if(_currentVector != NULL)
		{
			delete _currentVector;
			_currentVector = NULL;
		}
	}

	void VectorsReader::reset()
	{
		_minus = false;
		_decimalSeperator = false;
		_i = 0.1;
		_value = 0;
	}

	void VectorsReader::init()
	{
		reset();

		_firstVectorLength = -1;
		_lines = 0;
		_columns = 0;

		freeMemory();
		_vectors = new vector< vector< double >* >();
	}

	void VectorsReader::handleSeperator()
	{					
		_value = _minus == true ? -_value : _value;
		_currentVector->push_back(_value);

		reset();
	}

	void VectorsReader::handleNumber(char ch)
	{
		if(_decimalSeperator == false)
		{
			_value *= 10;
			_value  += ch - ZeroChar;
		}
		else
		{
			double d = (ch - ZeroChar)* _i;
			_i *= 0.1;
			_value += d;
		}
	}

	void VectorsReader::handleNewLine()
	{
		_value = _minus == true ? -_value : _value;
		_currentVector->push_back(_value);

		if(_firstVectorLength == -1)
			_firstVectorLength = _currentVector->size();
		else if(_firstVectorLength != _currentVector->size())
			throw AllVectorsShouldHaveTheSameLengthException();

		_vectors->push_back(_currentVector);
		_currentVector = new vector<double>();

		reset();

		_lines++;
		_columns = 0;
	}

	//*****************************************************************
	//PUBLIC METHODS
	//*****************************************************************

	VectorsReader::VectorsReader()
	{
		_vectors = NULL;
		_currentVector =  NULL;
	}

	VectorsReader::~VectorsReader()
	{
		freeMemory();
	}

	void VectorsReader::readData(const char* inputFile)
	{
		Timer t;
		t.start();

		init();

		ifstream fin(inputFile);
		if (fin.is_open())
		{
			_currentVector = new vector<double>();

			char ch;
			while (fin.get(ch))
			{	
				_columns++;

				if (ch >= ZeroChar && ch <= NineChar)
					handleNumber(ch);	
				else if (ch == DecimalSeperator)
					_decimalSeperator = true;
				else if (ch == Seperator)
					handleSeperator();
				else if (ch == EndOfLine)
					handleNewLine();
				else if (ch == MinusChar )
					_minus = true;
				else
					throw UnexpectedCharException(_lines, _columns);
			}

			fin.close();

			t.end();
			t.printResult(ElapsedTimeOfReadingData);
		}
	}
}