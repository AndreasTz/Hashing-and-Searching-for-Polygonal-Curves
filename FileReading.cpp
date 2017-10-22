#include <iostream>
#include <string.h>
#include <fstream>

#include "Grid.h"
#include "FileReading.h"
#include "HelpClasses.h"

using namespace std;


/*
Synartisi i opoia diavazei to input arxeio kai ektelei ton algorithmo gia mia mia kampili
	input: Filename (onoma arxeiou)
				 HashArray (Pinakas me deiktes se HashTables)
				 details (stoixeia voithitikis klasis gia ta arxika stoixeia pou prostithentai)
	output: -

	!!Aksizei na anaferthei, curveIDVec :: vector pou krataei ola ta id twn kampulwn pou diavazoyme
*/
void readingFromFile(string Filename , HashMap ** const HashArray,PreferedDetails * const details, vector<vector<double>>* v){

		ifstream myfile;
		myfile.open(Filename.c_str());
		if(myfile == NULL){
			cerr << " Problem in openning the file you've asked " << endl;
			exit(-2);
		}

		InitialCurve *info = new InitialCurve;

		string firstLineOfFile ;
		getline(myfile, firstLineOfFile);
		//cout << " First Line: " << firstLineOfFile << endl;

		string typeofFileStr = firstLineOfFile.substr (0,2);
		//cout << "STR::" << typeofFileStr << endl;
		string defaultForInputFile = "@d";
		string defaultForQueryFile = "R:";

		if(!typeofFileStr.compare(defaultForInputFile)){

			cout << "Exoume na kanoume me Input File" << endl;
      R = 1;
      if(firstLineOfFile.length() == 10){ // den exei allo orisma einai mono @dimension

        dimension = 2.0;

      }
      else{

        string dimStr = firstLineOfFile.substr (11,firstLineOfFile.length() - 11);
	      dimension = atof(dimStr.c_str());

      }
      cout << "dim:: " << dimension << endl;
		}
		else if(!typeofFileStr.compare(defaultForQueryFile)){

			cout << "Exoume na kanoume me Query File" << endl;
			string Rstr = firstLineOfFile.substr (3,firstLineOfFile.length() - 3);
			cout << Rstr << endl;
			R = atof(Rstr.c_str());
			cout << "R::: " << R << endl;

	}

	vector<int> curveNoOfPointsVec;

  string nextLineOfFile ;
  getline(myfile, nextLineOfFile);
	//	cout << " Next Line: " << nextLineOfFile << endl;

	while(!myfile.eof() && nextLineOfFile.compare("\n")){

    info -> curve_id = strtok ( const_cast<char*> (nextLineOfFile.c_str()),"\t, ");
		

    string noofPointsInCurveStr =  strtok( NULL , "\t, ");
    info -> noofPointsInCurve = atoi(noofPointsInCurveStr.c_str());
	curveNoOfPointsVec.push_back(info -> noofPointsInCurve);
		
    string pointStr;

    for(int i = 0; i < info -> noofPointsInCurve ; i++){

      for(int j = 0 ; j < (int)dimension ; j++){

			  pointStr = strtok (  NULL ,"()\t, ");
        info -> curvePoints[i][j] = atof(pointStr.c_str());
        cout << info -> curvePoints[i][j] << " " << endl;

			}
    }

	int curveid = atoi(info -> curve_id.c_str());
    operation(curveid, dimension, R, info->curvePoints , info->noofPointsInCurve , HashArray, details, v);

    nextLineOfFile;
	getline(myfile, nextLineOfFile);

	}
}
