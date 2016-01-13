/********************************************************************
 * Micha³ Komorowski
 * 2010-05-16
 * Implementation of a Neighborhood-Based Clustering Algorithm
 ********************************************************************/

#ifndef NEIGHBOURS_READER_H_
#define NEIGHBOURS_READER_H_

#include <vector>
#include <fstream>

#include "Constans.h"
#include "Exceptions.h"
#include "Interfaces.h"
#include "Utils.h"
#include "Timer.h"

using namespace std;

namespace NBC
{
	class NeighboursReader:
		public IIndexable< const vector<unsigned int>& >
	{
	private:

		// <summary>
		// Identifier of neighbour
		// </summary>
		int _id;

		// <summary>
		// Number of lines in the file
		// </summary>
		int _lines;
		// <summary>
		// Number of chars in the line
		// </summary>
		int _columns;

		// <summary>
		// Collection of identifiers of neighbours read from the file
		// </summary>
		vector< vector< unsigned int >* >* _neighbours;
		// <summary>
		// Neighbours being currently read from the file
		// </summary>
		vector<unsigned int>* _currentNeighbours;

		// <summary>
		// Free the memory allocated by the algorithm
		// </summary>
		void freeMemory();

		// <summary>
		// Initialize the fields of the class
		// </summary>
		void init();

		// <summary>
		// Handle identifiers seperator char in the file
		// </summary>
		void handleSeperator();
		// <summary>
		// Handle numeric char in the file
		// </summary>
		void handleNumber(char ch);
		// <summary>
		// Handle new line in the file
		// </summary>
		void handleNewLine();

	public:
		__declspec(dllexport) NeighboursReader();

		__declspec(dllexport) ~NeighboursReader();

		__declspec(dllexport) void readData(const char* inputFile);

		__declspec(dllexport) unsigned int size() const
		{
			return _neighbours->size();
		}

		__declspec(dllexport) const vector<unsigned int>& at(unsigned int i) const
		{
			return *(_neighbours->at(i));
		}

		__declspec(dllexport) const vector<unsigned int>& operator[](unsigned int i) const
		{
			return *(_neighbours->at(i));
		}
	};
}

#endif