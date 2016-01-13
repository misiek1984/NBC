/********************************************************************
* Micha³ Komorowski
* 2010-05-16
* Implementation of a Neighborhood-Based Clustering Algorithm
********************************************************************/

#include "Main.h"

int main(int argc, char** argv)
{
	NBC::Main().main(argc, argv);
}

namespace NBC
{
	void Main::reset()
	{
		_fromK= -1;
		_toK= -1;
		_step= -1;
		_inputFile = NULL;
		_outputFile = NULL;
		_neighbours = NULL;
		_writeNeighbours = false;
		_writeCompleteData = false;
		_generateNeighboursFilesNames = false;
	}

	void Main::printHelp()
	{
		cout<<"nbc.exe -k|(-from -to -step) -input fileName -output -fileName "<<endl;
		cout<<"[-neighbours fileName [-generateNeighboursFilesNames]] [-writeNeighbours ] [-writeCompleteData]"<<endl;
	};

	bool Main::processArguments(int argc, char** argv)
	{
		reset();

		int i = 1;
		while(i < argc)
		{
			char* s = argv[i];

			if(strcmp(s, "-writeNeighbours")== 0)
				_writeNeighbours = true;
			else if(strcmp(s, "-writeCompleteData")== 0)
				_writeCompleteData = true;
			else if(strcmp(s, "-generateNeighboursFilesNames")== 0)
				_generateNeighboursFilesNames = true;
			else
			{
				if(i == argc - 1)
					return false;

				if(strcmp(s, "-k") == 0)
				{
					int k;
					if(!Utils::from_string<int>(k, string(argv[i+1]), std::dec))
						return false;

					_fromK = k;
					_toK = k + 1;
					_step = 1;
				}
				else if(strcmp(s, "-from")== 0)
				{
					if(!Utils::from_string<int>(_fromK, string(argv[i+1]), std::dec))
						return false;
				}
				else if(strcmp(s, "-to")== 0)
				{
					if(!Utils::from_string<int>(_toK, string(argv[i+1]), std::dec))
						return false;
				}
				else if(strcmp(s, "-step")== 0)
				{
					if(!Utils::from_string<int>(_step, string(argv[i+1]), std::dec))
						return false;
				}
				else if(strcmp(s, "-input")== 0)
					_inputFile = argv[i+1];
				else if(strcmp(s, "-output")== 0)
					_outputFile = argv[i+1];
				else if(strcmp(s, "-neighbours")== 0)
					_neighbours= argv[i+1];
				else
					return false;

				++i;
			}

			++i;
		}

		if(_fromK == -1 || _toK == -1 || _step == -1 || _inputFile == NULL || _outputFile == NULL)
			return false;

		if(_fromK <= 0 || _toK <= 0 || (_step >= 0 && _fromK > _toK) || (_step <= 0 && _fromK < _toK))
			return false;
		
		if(_generateNeighboursFilesNames == true && _neighbours == NULL)
			return false;

		return true;
	}

	void Main::writeOutput(int k, const NBCAlgorithm& alg)
	{
		{
			ostringstream ss;
			ss<<_outputFile<<"_"<<k;

			Logger::instance()<<"Writing result to output file: "<<ss.str()<<NewLine;

			alg.writeClustersToFile(ss.str().c_str());
		}

		if(_writeNeighbours)
		{
			ostringstream ss;
			ss<<_outputFile<<"_"<<k<<"_neighbours";

			Logger::instance()<<"Writing neighbours to output file: "<<ss.str()<<NewLine;
			alg.writeNeighboursToFile(ss.str().c_str());
		}

		if(_writeCompleteData)
		{
			ostringstream ss;
			ss<<_outputFile<<"_"<<k<<"_completeAlgorithmData";

			Logger::instance()<<"Writing complete algorithm data to file: "<<ss.str()<<NewLine;
			alg.writeCompleteAlgorithmDataToFile(ss.str().c_str());
		}
	}

	void Main::main(int argc, char** argv)
	{
		if(!processArguments(argc, argv))
		{
			printHelp();
			return;
		}

		Logger::instance().init(_outputFile, true);
		Logger::instance().writeHeader();
		Logger::instance()<<NewLine<<"Input file: "<<_inputFile<<NewLine;

		try
		{
			Timer::enable();

			NBCAlgorithm alg = NBCAlgorithm();

			VectorsReader vectorsReader;
			Logger::instance()<<"Reading data from input file..."<<NewLine;
			vectorsReader.readData(_inputFile);
			alg.setData(&vectorsReader);

			Logger::instance()<<"Number of vectors: "<<vectorsReader.size()<<NewLine;

			NeighboursReader neighboursReader;
			if(!_generateNeighboursFilesNames && _neighbours != NULL)
			{
				Logger::instance()<<"Reading neighbours from file "<<_neighbours<<NewLine;
				neighboursReader.readData(_neighbours);
				alg.setNeighbours(&neighboursReader);
			}

			for(int k = _fromK; k < _toK; k = k + _step)
			{
				Logger::instance()<<NewLine<<"Calculations with k = "<<k<<NewLine;

				if(_generateNeighboursFilesNames)
				{
					ostringstream ss;
					ss<<_neighbours<<"_"<<k<<"_neighbours";

					Logger::instance()<<"Reading neighbours from file "<<ss.str()<<NewLine;
					neighboursReader.readData(ss.str().c_str());
					alg.setNeighbours(&neighboursReader);
				}

				alg.start(k);

				Logger::instance()<<"Number of clusters: "<<alg.getNumberOfClusters()<<NewLine;

				writeOutput(k, alg);

				Logger::instance()<<NewLine;
			}
		}
		catch(NBCException ex)
		{
			Logger::instance()<<ex<<NewLine;
		}

		//Logger::instance().flush();
		cout<<"Press any key to continue";
		cin.get();
	}
}
