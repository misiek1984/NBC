/********************************************************************
* Micha³ Komorowski
* 2010-05-16
* Implementation of a Neighborhood-Based Clustering Algorithm
********************************************************************/

#include "NBC.h"

namespace NBC
{
	//*****************************************************************
	//PRIVATE METHODS
	//*****************************************************************

	void NBCAlgorithm::freeMemory()
	{
		for(unsigned int i = 0; i < _vectorsData.size(); ++i)
			delete _vectorsData[i];

		_vectorsData.clear();
	}

	void NBCAlgorithm::calculateNDF()
	{
		_calculateNDFTimer.start();

		for(unsigned int i = 0; i < _vectors->size(); ++i)
			_vectorsData.push_back(new VectorData());

		if(_neighbours != NULL)
		{
			for(unsigned int i = 0; i < _vectors->size(); ++i)
			{
				VectorData* d = _vectorsData.at(i);

				const vector<unsigned int>& neighbours = _neighbours->at(i);
				for(unsigned int j = 0; j < neighbours.size() && j < _k; ++j)
					addTokNB(d, neighbours.at(j));
			}
		}
		else
		{
			int counter = 0;
			int step = _vectors->size() / 20;
			for(unsigned int i = 0; i < _vectors->size(); ++i)
			{
				calculatekNB(i);

				if(i != 0 && i % step == 0)
				{
					counter++;
					Logger::instance()<<counter*5<<"% ";
				}
			}
			Logger::instance()<<NewLine;
		}

		for(unsigned int i = 0; i < _vectors->size(); ++i)
		{
			VectorData* d = _vectorsData[i];
			d->NDF = d->RkNB / (double)d->kNB.size();
		}

		_calculateNDFTimer.end();
		_calculateNDFTimer.printResult(ElapsedTimeOfCalculatingNDF);
	}

	void NBCAlgorithm::calculatekNB(unsigned int indexOfVector)
	{	
		_distances.clear();
		calculateDistances(indexOfVector);
		sort(_distances.begin(), _distances.end(), distanceComparer);
		chooseKNearest(indexOfVector);
	}

	void NBCAlgorithm::calculateDistances(unsigned int indexOfVector)
	{
		//Calculate distances between i'th and all other vectors
		for(unsigned int j = 0; j < _vectors->size(); ++j)
		{
			if(indexOfVector != j)
			{
				double dist = calculateDistance(indexOfVector, j);
				_distances.push_back(pair<unsigned int, double>(j, dist));
			}	
		}
	}

	double NBCAlgorithm::calculateDistance(unsigned int index1, unsigned int index2)
	{
		const vector<double>& v1 = _vectors->at(index1);
		const vector<double>& v2 = _vectors->at(index2);

		if(v1.size() != v2.size())
			throw AllVectorsShouldHaveTheSameLengthException();

		double res = 0;
		for (unsigned int i = 0; i < v1.size(); ++i)
			res += (v1[i] - v2[i])*(v1[i] - v2[i]);

		return pow(res, 0.5);
	}


	void NBCAlgorithm::chooseKNearest(unsigned int indexOfVector)
	{		
		VectorData* d = _vectorsData[indexOfVector];

		double dist = -1;
		if(_distances.size() >= _k)
			dist = _distances[_k-1].second;

		//Choose k nearest vectors 
		for(int i = 0; i < _k && i < _distances.size(); ++i)
		{
			const pair<unsigned int, double>& currentPair = _distances[i];

			if(i < _k || dist == currentPair.second)
				addTokNB(d, currentPair.first);
		}
	}

	void NBCAlgorithm::addTokNB(VectorData* vector, unsigned int neighbour)
	{
		vector->kNB.push_back(neighbour);

		//If vector A belong to the kNB set of the vector B it means that vector B
		//belong to the R-kNB set of the vector A
		_vectorsData[neighbour]->RkNB++;
	}

	void NBCAlgorithm::clustering()
	{
		_clusteringTimer.start();

		_results.clear();

		//Allocate memory for results
		for(unsigned int i = 0; i < _vectors->size(); ++i)	
			_results.push_back(-1);

		for (int i = 0; i < _vectorsData.size(); ++i)
		{
			VectorData* d = _vectorsData[i];
			if( d->NDF < 1 || _results[i] != -1)
				continue;

			_results[i] = _numberOfClusters;

			list<int> toCheck;
			for(int j = 0; j < d->kNB.size(); ++j)
			{
				unsigned int temp = d->kNB[j];
				_results[temp] = _numberOfClusters;

				if(_vectorsData[temp]->NDF >= 1)
					toCheck.push_front(temp);
			}

			//Expanding cluster
			while(toCheck.size() > 0)
			{
				d = _vectorsData[toCheck.back()];
				toCheck.pop_back();

				for(int j = 0; j < d->kNB.size(); ++j)
				{
					unsigned int temp = d->kNB[j];

					if(_results[temp] != -1)
						continue;

					_results[temp] = _numberOfClusters;

					if(_vectorsData[temp]->NDF >= 1)
						toCheck.push_front(temp);	
				}
			}

			_numberOfClusters++;
		}

		_clusteringTimer.end();
		_clusteringTimer.printResult(ElapsedTimeOfClustering);
	}

	//*****************************************************************
	//PUBLIC METHODS
	//*****************************************************************

	NBCAlgorithm::~NBCAlgorithm()
	{
		freeMemory();
	}

	void NBCAlgorithm::start(unsigned int k)
	{
		if(_vectors == NULL)
			throw NBCException("No input data!");

		if(_neighbours != NULL && _neighbours->size() != _vectors->size())
			throw NBCException("Number of vectors in input data is different than number of neighbours' sets!");

		_startTimer.start();

		freeMemory();
		_numberOfClusters = 0;
		_k = k > 0 ? k : 5;

		calculateNDF();
		clustering();

		_startTimer.end();
		_startTimer.printResult(ElapsedTimeOfNBC);
	}


	void NBCAlgorithm::writeClustersToFile(const char* fileName) const
	{
		ofstream fout(fileName, ios_base::trunc);
		if(fout.is_open())
		{
			for(int j = 0; j < _results.size(); ++j)
				fout<<_results.at(j)<<endl;

			fout.close();
		}
	}

	void NBCAlgorithm::writeNeighboursToFile(const char* fileName) const
	{
		ofstream fout(fileName, ios_base::trunc);

		if(fout.is_open())
		{
			for(int j = 0; j < _vectorsData.size(); ++j)
			{
				VectorData* d = _vectorsData.at(j);
				for(int k = 0; k < d->kNB.size(); ++k)
					fout<<d->kNB.at(k)<<WhiteSpace;

				fout<<endl;
			}

			fout.close();
		}
	}
	void NBCAlgorithm::writeCompleteAlgorithmDataToFile(const char* fileName) const
	{
		ofstream fout(fileName, ios_base::trunc);
	
		locale myloc(  locale(),    // C++ default locale
                  new WithComma());// Own numeric facet

		fout.imbue(myloc);

		if(fout.is_open())
		{
			fout<<"CLUSTER_NUMBER NDF RKNB NUMBER_OF_NEIGHBOURS (NEIGHBOURS)"<<endl;
			for(int j = 0; j < _vectorsData.size(); ++j)
			{
				VectorData* d = _vectorsData.at(j);
				fout<<_results.at(j);
				fout<<WhiteSpace;
				fout<<d->NDF;
				fout<<WhiteSpace;
				fout<<d->RkNB;
				fout<<WhiteSpace;
				fout<<d->kNB.size();
				fout<<WhiteSpace<<"(";

				for(int k = 0; k < d->kNB.size(); ++k)
				{
					int id = d->kNB.at(k);
					if(k != d->kNB.size() - 1)
						fout<<"id"<<id<<"c"<<_results.at(id)<<WhiteSpace;
					else
						fout<<"id"<<id<<"c"<<_results.at(id)<<")";
				}

				fout<<endl;
			}

			fout.close();
		}
	}
}