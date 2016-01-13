/********************************************************************
* Micha³ Komorowski
* 2010-05-16
* Implementation of a Neighborhood-Based Clustering Algorithm
********************************************************************/

#include "NeighboursReader.h"

namespace NBC
{
	//*****************************************************************
	//PRIVATE METHODS
	//*****************************************************************

	void NeighboursReader::freeMemory()
	{
		if(_neighbours != NULL)
		{
			Utils::freeVectorOfVectors(_neighbours );
			_neighbours = NULL;
		}

		if(_currentNeighbours  != NULL)
		{
			delete _currentNeighbours ;
			_currentNeighbours  = NULL;
		}
	}

	void NeighboursReader::init()
	{
		_id = -1;

		_lines = 0;
		_columns = 0;

		freeMemory();
		_neighbours  = new vector< vector< unsigned int >* >();
	}

	void NeighboursReader::handleSeperator()
	{			
		if(_id != -1)
			_currentNeighbours ->push_back(_id);

		_id = -1;
	}

	void NeighboursReader::handleNumber(char ch)
	{
		if(_id == -1)
			_id = 0;

		_id *= 10;
		_id  += ch - ZeroChar;
	}

	void NeighboursReader::handleNewLine()
	{
		if(_id != - 1)
			_currentNeighbours ->push_back(_id);

		_neighbours ->push_back(_currentNeighbours );
		_currentNeighbours = new vector<unsigned int>();

		_id = -1;
		_lines++;
		_columns = 0;
	}

	//*****************************************************************
	//PUBLIC METHODS
	//*****************************************************************

	NeighboursReader::NeighboursReader()
	{
		_neighbours  = NULL;
		_currentNeighbours =  NULL;
	}

	NeighboursReader::~NeighboursReader()
	{
		freeMemory();
	}

	void NeighboursReader::readData(const char* inputFile)
	{
		Timer t;
		t.start();

		init();

		ifstream fin(inputFile);
		if (fin.is_open())
		{
			_currentNeighbours  = new vector<unsigned int>();

			char ch;
			while (fin.get(ch))
			{	
				_columns++;

				if (ch >= ZeroChar && ch <= NineChar)
					handleNumber(ch);	
				else if (ch == WhiteSpace)
					handleSeperator();
				else if (ch == EndOfLine)
					handleNewLine();
				else
					throw UnexpectedCharException(_lines, _columns);
			}

			fin.close();

			t.end();
			t.printResult(ElapsedTimeOfReadingData);
		}
	}
}