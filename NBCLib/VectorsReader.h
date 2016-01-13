/********************************************************************
 * Micha³ Komorowski
 * 2010-05-16
 * Implementation of a Neighborhood-Based Clustering Algorithm
 ********************************************************************/

#ifndef VECTORS_READER_H_
#define VECTORS_READER_H_

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
	class VectorsReader:
		public IIndexable< const vector<double>& >
	{
	private:

		// <summary>
		// Was minus sign read from file
		// </summary>
		bool _minus;
		// <summary>
		// Was decimal seperator read from file
		// </summary>
		bool _decimalSeperator;
		// <summary>
		// To calculate fraction of the coordinates 
		// </summary>
		double _i;
		// <summary>
		// Value of the coordinates of the vector
		// </summary>
		double _value;
		// <summary>
		// The length of the first vector in the file
		// </summary>
		unsigned int _firstVectorLength;

		// <summary>
		// Number of lines in the file
		// </summary>
		int _lines;
		// <summary>
		// Number of chars in the line
		// </summary>
		int _columns;

		// <summary>
		// Collection of vectors read from the file
		// </summary>
		vector< vector< double >* >* _vectors;
		// <summary>
		// Vector being currently read from the file
		// </summary>
		vector<double>* _currentVector;

		// <summary>
		// Free the memory allocated by the algorithm
		// </summary>
		void freeMemory();

		// <summary>
		// Initialize the fields of the class
		// </summary>
		void init();
		// <summary>
		// Reset the state fields of the class
		// </summary>
		void reset();

		// <summary>
		// Handle coordinates seperator char in the file
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
		__declspec(dllexport) VectorsReader();

		__declspec(dllexport) ~VectorsReader();

		__declspec(dllexport) void readData(const char* inputFile);

		__declspec(dllexport) unsigned int size() const
		{
			return _vectors->size();
		}

		__declspec(dllexport) const vector<double>& at(unsigned int i) const
		{
			return *(_vectors->at(i));
		}

		__declspec(dllexport) const vector<double>& operator[](unsigned int i) const
		{
			return *(_vectors->at(i));
		}
	};
}

#endif