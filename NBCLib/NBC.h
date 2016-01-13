/********************************************************************
* Micha³ Komorowski
* 2010-05-16
* Implementation of a Neighborhood-Based Clustering Algorithm
********************************************************************/

#ifndef NBC_H_
#define NBC_H_

#include <math.h>
#include <algorithm>
#include <vector>
#include <list>

#include "Constans.h"
#include "Exceptions.h"
#include "Utils.h"
#include "VectorsReader.h"
#include "NeighboursReader.h"
#include "Interfaces.h"
#include "Timer.h"
#include "Logger.h"

namespace NBC
{
	class NBCAlgorithm
	{
	private:

		class VectorData
		{
		public:
			// <summary>
			// Indexes of vectors that belong to the kNB set of a particular vector
			// </summary>
			vector<unsigned int> kNB;
			// <summary>
			// Number of vectors in the R-kNB set of a particular vector
			// </summary>
			unsigned int RkNB;
			// <summary>
			// Value of the NDF measure 
			// </summary>
			double NDF;

			VectorData(): RkNB(0), NDF(0) {}
		};

		Timer _startTimer;
		Timer _clusteringTimer;
		Timer _calculateNDFTimer;

		// <summary>
		// Input data/vectors
		// </summary>
		const IIndexable< const vector<double>& >* _vectors;

		// <summary>
		// Neighbours for vectors that was read from the file
		// </summary>
		const IIndexable< const vector<unsigned int>& >* _neighbours;

		// <summary>
		// The results of calculations for input vectors
		// </summary>
		vector< VectorData* > _vectorsData;

		// <summary>
		// The result of classification
		// </summary>
		vector<int> _results;

		// <summary>
		// The distances
		// </summary>
		vector< pair<unsigned int, double> > _distances;

		// <summary>
		// Parameter k of NBC algorithm
		// </summary>
		unsigned int _k;

		// <summary>
		// Number of clusters
		// </summary>
		unsigned int _numberOfClusters;

		// <summary>
		// Free the memory allocated by the algorithm
		// </summary>
		void freeMemory();

		// <summary>
		// Calculates NDF measure for input data
		// </summary>
		void calculateNDF();

		// <summary>
		// Calculates number of vectors in the kNB set. Additionally the number of
		// vectors in R-kNB set is calculated for vectors othe that i'th vector.
		// </summary>
		// <param name="i">Index of vector in the input data</param>
		void calculatekNB(unsigned int i);

		// <summary>
		// Calculate distance between  i'th vector and other.
		// </summary>
		// <param name="indexOfVector">Index of vector in the input data</param>
		void calculateDistances(unsigned int indexOfVector);

		// <summary>
		// Calculate distance between two vectors.
		// </summary>
		// <param name="index1">Index of first vector</param>
		// <param name="index2">Index of second vector</param>
		double calculateDistance(unsigned int index1, unsigned int index2);

		// <summary>
		// Choose k nearest neighboors for i'th vector
		// </summary>
		// <param name="indexOfVector">Index of vector in the input data</param>
		void chooseKNearest(unsigned int indexOfVector);

		// <summary>
		// Add vector to the kNB set of other vector
		// </summary>
		// <param name="vector"></param>
		// <param name="neighbour)"></param>
		void addTokNB(VectorData* vector, unsigned int neighbour);

		// <summary>
		// Calculate clusters based on the prior calculations.
		// </summary>
		void clustering();

		// <summary>
		// The method need to sort distances between vectors.
		// </summary>
		static bool distanceComparer (pair<unsigned int, double> i, pair<unsigned int, double> j) { return (i.second < j.second); }
	public:
		__declspec(dllexport) ~NBCAlgorithm();

		__declspec(dllexport) NBCAlgorithm() : _vectors(NULL), _neighbours(NULL)
		{}

		// <summary>
		// Start the algorithm
		// </summary>
		// <param name="k">Parameter k of NBC algorithm</param>
		__declspec(dllexport) void start(unsigned int k);

		__declspec(dllexport) unsigned int getNumberOfClusters() { return _numberOfClusters; }

		__declspec(dllexport) void writeClustersToFile(const char* fileName) const;

		__declspec(dllexport) void writeNeighboursToFile(const char* fileName) const;

		__declspec(dllexport) void writeCompleteAlgorithmDataToFile(const char* fileName) const;

		__declspec(dllexport) void setData(const IIndexable< const vector<double>& >* v) { _vectors = v; };

		__declspec(dllexport) void setNeighbours(const IIndexable< const vector<unsigned int>& >* n) { _neighbours = n; };
	};
}

#endif