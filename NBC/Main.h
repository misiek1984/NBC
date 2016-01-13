/********************************************************************
* Micha³ Komorowski
* 2010-05-16
* Implementation of a Neighborhood-Based Clustering Algorithm
********************************************************************/

#ifndef MAIN_H_
#define MAIN_H_

#include <iostream>
#include <sstream>

#include "NBC.h"

using namespace std;

namespace NBC
{
	class Main
	{
	private:
		int _fromK;
		int _toK;
		int _step;
		char* _inputFile;
		char* _outputFile;
		char* _neighbours;
		bool _writeNeighbours;
		bool _writeCompleteData;
		bool _generateNeighboursFilesNames;

		ofstream _log;

		void reset();

		void printHelp();

		bool processArguments(int argc, char** argv);

		void writeOutput(int k, const NBCAlgorithm& alg);

	public:

		void main(int argc, char** argv);
	};
}

#endif