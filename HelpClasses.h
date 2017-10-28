#ifndef HELPCLASSES__H
#define HELPCLASSES__H


#define DEFAULT_K 2
#define DEFAULT_L 3

#include <string>
#include <vector>
using namespace std;

struct queryDetails {
		string queryID;
		bool foundGridCurve;
		int LSHDistance;
		int trueDistance;

		string trueNearestNeighbor;
		string LSHNearestNeighbor;

		vector<string> NNcurves;

		queryDetails()
		{
			this->foundGridCurve = false;
		}
};


class PreferedDetails{

	public:
		string inputFile;
		string queryFile;
		string outputFile;

		string typeOfFunctionChoice;
		string typeOfHashChoice;

		string optionOfStat;

		int numberOfLocalitySensitiveFunctions;
		int numberOfHashingArrays;

		int optionalStatsIsHere;

		PreferedDetails(){
			this -> optionalStatsIsHere  = 0;  //gia tin periptwsi pou den dothei
			this -> numberOfHashingArrays = DEFAULT_L;  //gia tin periptwsi pou den dothei
			this -> numberOfLocalitySensitiveFunctions = DEFAULT_K;  //gia tin periptwsi pou den dothei
		}

};

#endif
