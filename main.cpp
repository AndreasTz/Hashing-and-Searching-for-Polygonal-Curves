#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <ctime>

#include "FileReading.h"
#include "Hashing.h"
#include "HelpClasses.h"

#include "Grid.h"
#include "outputFunctions.h"

#define DEFAULT_K 2
#define DEFAULT_L 3
#define minus_d  "-d"
#define minus_q  "-q"
#define minus_o  "-o"
#define minus_k  "-k"
#define minus_L  "-L"
#define minus_Stats "-stats"
#define minus_Function "-function"
#define minus_Hash "-hash"

using namespace std;


void readingFromCMD(int howManyArgs, char const *argv[] , PreferedDetails& details);
void menu(PreferedDetails& details);
void showPreferences(PreferedDetails& details);
string checkForContinue();

vector<stats> statsVec;
//vector<double> LSHTime;

int main(int argc , char const *argv[]){

	string answer = "yes";
	int times = 0;
	while(answer == "yes"){

		PreferedDetails details;
		cout << "times: " << times << endl;
		if(argc == 1 || times > 1) {

				menu(details);

		}
		else{

				readingFromCMD( argc, argv , details);

		}

		showPreferences(details);
		int count = 200;
		if(details.optionalStatsIsHere){
			count = 0 ;
		}
		vector<queryDetails> queryOfVector;
		vector<vector<double>> gridVector;
		vector<string> nameVector;
		int flagBasicFuncCall;
		do{

			nameVector.clear();
			gridVector.clear();
			queryOfVector.clear();
      /*********************************************************
      //for each curve we do
      gridVector.push_back(double**array);
      //we print or access like:
      gridVector[i][n][m] //i = curveID - 1, n/m = diastaseis
      *********************************************************/

			HashMap ** HashArray;

			HashArray = new HashMap* [details.numberOfHashingArrays];

			for(int i = 0; i < details.numberOfHashingArrays ; i++){
				HashArray[i] = new HashMap();
			}

			flagBasicFuncCall = 0;
      readingFromFile(flagBasicFuncCall, details.inputFile , HashArray, details, gridVector, nameVector, queryOfVector);

			flagBasicFuncCall = 0;
			readingFromFile(flagBasicFuncCall, details.queryFile , HashArray, details, gridVector, nameVector, queryOfVector);


	//		cout << "end query " << endl;
	/*		cout << "The names of curves are: " << endl;
			for(auto& x : nameVector){
				cout << x << " , ";
			}
			cout << endl;
			cout << "The ids are: "
			for(auto& x : gridVector){
				for(auto& y : x){
					cout << y << endl;
				}
			}
	*/
			//////////////////////TESTING GROUND********************
			count++;

			for(int i = 0; i < details.numberOfHashingArrays ; i++){
					delete HashArray[i];
			}


		}while(count < 100);
			writingToOutputFile(details.outputFile, queryOfVector, statsVec, details);
		times++;

		answer = checkForContinue();
	}
		statsVec.clear();
		return 0;
}


string checkForContinue(){
	string answer;
	while(1){
			cout << "Do you want to continue for a different input? (yes / no)" << endl;
			cin >> answer;

			if(answer.compare("yes") && answer.compare("no")){
				cout << "Please enter yes or no" << endl;
			}
			else{
				getchar();
				return(answer);
				//break;
			}
	}
}


void showPreferences(PreferedDetails& details){

	cout << "Your prefereces are: " << endl;
	cout << "Input File: " << details.inputFile << endl;
	cout << "Output File: " << details.outputFile << endl;
	cout << "Query File: " << details.queryFile << endl;
	cout << "number of Locality Sensitive Functions: " << details.numberOfLocalitySensitiveFunctions << endl;
	cout << "numberOfHashingArrays: " << details.numberOfHashingArrays << endl;
	cout << "optional Stats Is Here: " << details.optionalStatsIsHere << endl;
	cout << "type of Function Choice: " << details.typeOfFunctionChoice << endl;
	cout << "type of Hash Choice: " << details.typeOfHashChoice << endl;

}



void menu(PreferedDetails& details){

	details.optionalStatsIsHere = 0;

	cout << " Welcome to our menu " << endl;
	cout << " Please enter the path of INPUT FILE " << endl;
 	cin >> details.inputFile;

	string numberofLocalitySensitiveFunctionsStr;

	cout << " Please enter the number of Locality Sensitive Functions: (If you press enter the default values will be inserted) " << endl;
	cin >> numberofLocalitySensitiveFunctionsStr;

	if ( numberofLocalitySensitiveFunctionsStr == ""){

		details.numberOfLocalitySensitiveFunctions = DEFAULT_K;

	}
	else{

		details.numberOfLocalitySensitiveFunctions = atoi(numberofLocalitySensitiveFunctionsStr.c_str());

	}

	cout << " Please enter the number of Hashing Arrays: (If you press enter the default values will be inserted) " << endl;

	string numberOfHashingArraysStr;
	cin >> numberOfHashingArraysStr;

	if ( numberOfHashingArraysStr == ""){

		details.numberOfHashingArrays = DEFAULT_L;

	}
	else{

		details.numberOfHashingArrays = atoi(numberOfHashingArraysStr.c_str());

	}

	cout << " Please enter the type of Function (DFT or DTW) " << endl;
	cin >> details.typeOfFunctionChoice;
	while( details.typeOfFunctionChoice.compare("DFT") && details.typeOfFunctionChoice.compare("DTW") ) {
		cout << " Please \" DFT \" or \" DTW \" " << endl;
		getline(cin, details.typeOfFunctionChoice);
	}

	cout << " Please enter the type of Hash (classic or probabilistic) " << endl;
	cin >> details.typeOfHashChoice;
	while( details.typeOfHashChoice.compare("classic") && details.typeOfHashChoice.compare("probabilistic") ) {
		cout << " Please \" classic \" or \" probabilistic \" " << endl;
		getline(cin, details.typeOfHashChoice);
	}

	while(1) {
		cout << " Do you want stats? (yes/no)" << endl;
		string answer;
		cin >> answer;
		if(!answer.compare("yes")){

			details.optionalStatsIsHere = 1;
			break;

		}
		else if (!answer.compare("no")){
			break;
		}
		else {
			cout << "Please answer yes or no" << endl;
		}
	}


	cout << " Please enter the path of OUTPUT FILE " << endl;
	cin >> details.outputFile;

	cout << " Please enter the path of QUERY FILE " << endl;
	cin >> details.queryFile;
}


/*
	CMD::::!!!!!!!!!!!!!!! Yparxei dinatotita na dineis -stats <otidipote> kai apla -stats <keno>
	Menu:::: !!!!!!!!!!!!!! yparxei sinthiki elegxou gia na dinetai yes/no
*/
void readingFromCMD(int howManyArgs, char const *argv[] , PreferedDetails& details) {

	string arg;

 	for(int i = 1 ; i < howManyArgs ; i+=2){

		arg = argv[i];

		if(!arg.compare(minus_d)){

			details.inputFile = argv[i+1];

		}
		else if(!arg.compare(minus_q)){

			details.queryFile = argv[i+1];
			//cout << "Query File: " << details->queryFile << endl;
		}
		else if(!arg.compare(minus_o)){

			details.outputFile = argv[i+1];
		//	cout << "Output File: " << details->outputFile << endl;
		}
		else if(!arg.compare(minus_k)){

			arg = argv[i+1];
			details.numberOfLocalitySensitiveFunctions = atoi(arg.c_str());
		//	cout << "number of Locality Sensitive Functions: " << details->numberOfLocalitySensitiveFunctions << endl;
		}
		else if(!arg.compare(minus_L)){

			arg = argv[i+1];
			details.numberOfHashingArrays = atoi(arg.c_str());
		//	cout << "numberOfHashingArrays: " << details->numberOfHashingArrays << endl;
		}
		else if(!arg.compare(minus_Stats)){

			details.optionalStatsIsHere = 1;

			arg = argv[i+1];

			if(arg == ""){

				i=i-1;
				details.optionOfStat = "";

			}
			else{

				details.optionOfStat = argv[i+1];

			}

		}
		else if(!arg.compare(minus_Function)){

			details.typeOfFunctionChoice = argv[i+1];

		}
		else if(!arg.compare(minus_Hash)){

			details.typeOfHashChoice = argv[i+1];

		}

	}

}
