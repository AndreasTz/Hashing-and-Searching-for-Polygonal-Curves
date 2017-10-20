#ifndef HELPCLASSES__H
#define HELPCLASSES__H


#define DEFAULT_K 2
#define DEFAULT_L 3

#include <string>
using namespace std;

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
