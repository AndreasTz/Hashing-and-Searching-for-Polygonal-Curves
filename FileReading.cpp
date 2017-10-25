#include <iostream>
#include <string.h>
#include <fstream>

#include "Grid.h"
#include "FileReading.h"
#include "HelpClasses.h"

using namespace std;

double R, dimension;

/*
Sunartisi i opoia upologizei ta vasika stixeia tis kampilis sumfwna me to dothen input arxeio gia mia sygkekrimeni grammi
*/
void EstimateCurveDetails(InitialCurve *info, string nextLineOfFile, vector<int> *curveNoOfPointsVec){
	info -> curve_id = strtok ( const_cast<char*> (nextLineOfFile.c_str()),"\t, ");
	string noofPointsInCurveStr =  strtok( NULL , "\t, ");
	info -> noofPointsInCurve = atoi(noofPointsInCurveStr.c_str());
	curveNoOfPointsVec->push_back(info -> noofPointsInCurve);
	string pointStr;

	for(int i = 0; i < info -> noofPointsInCurve ; i++){
		for(int j = 0 ; j < (int)dimension ; j++){

			pointStr = strtok (  NULL ,"()\t, ");
			info -> curvePoints[i][j] = atof(pointStr.c_str());
			cout << info -> curvePoints[i][j] << " " << endl;

		}
	}
}


/*Sunartisi i opoia upologizei to eidos toy arxeiou
Returns 1: an einai input arxeio
Returns 2: an einai query arxeios*/
int DetermineTypeOfFile(ifstream* myfile){

	string firstLineOfFile ;
	getline(*myfile, firstLineOfFile);

	string typeofFileStr = firstLineOfFile.substr (0,2);
	string defaultForInputFile = "@d";
	string defaultForQueryFile = "R:";

	if(!typeofFileStr.compare(defaultForInputFile)){
		cout << "Input File" << endl;
		R = 1;
		if(firstLineOfFile.length() == 10){ // den exei allo orisma einai mono @dimension

			dimension = 2.0;

		}
		else{

			string dimStr = firstLineOfFile.substr (11,firstLineOfFile.length() - 11);
			dimension = atof(dimStr.c_str());

		}
		return 1;
	}
	else if(!typeofFileStr.compare(defaultForQueryFile)){

		cout << "Query File" << endl;
		string Rstr = firstLineOfFile.substr (3,firstLineOfFile.length() - 3);
		cout << Rstr << endl;
		R = atof(Rstr.c_str());
		//cout << "R::: " << R << endl;
		return 2;
	}
}


/*Sunartisi pou diavazei mia- mia tin grammi enos queryFile*/
string readQueryFileLineByLine(ifstream *myfile){
	string Line;
	getline(*myfile, Line);
	if(!myfile->eof() && Line.compare("\n")){

	cout << "LIne:: " << Line << endl;

	vector<int> curveNoOfPointsVec;
	InitialCurve *info = new InitialCurve;

	EstimateCurveDetails(info, Line, &curveNoOfPointsVec);
	cout << info -> curve_id << endl;
	return Line;
}
}


/*
Synartisi i opoia diavazei to input arxeio kai ektelei ton algorithmo gia mia mia kampili
	input: Filename (onoma arxeiou)
				 HashArray (Pinakas me deiktes se HashTables)
				 details (stoixeia voithitikis klasis gia ta arxika stoixeia pou prostithentai)
	output: -

*/
HashEntry* readingFromFile(string Filename, HashMap ** const HashArray,PreferedDetails * const details, vector<vector<double>>* v){
		cout << "FILENAME: "<<	Filename << endl;
		ifstream myfile;
		myfile.open(Filename.c_str());
		if(myfile == NULL){
			cerr << " Problem in openning the file you've asked " << endl;
			exit(-2);
		}

		int type = DetermineTypeOfFile(&myfile);

		if(type == 1){ // is Input File
			vector<int> curveNoOfPointsVec;
			InitialCurve *info = new InitialCurve;
  		string nextLineOfFile ;
  		getline(myfile, nextLineOfFile);
			while(!myfile.eof() && nextLineOfFile.compare("\n")){
				EstimateCurveDetails(info, nextLineOfFile, &curveNoOfPointsVec);
				int curveid = atoi(info -> curve_id.c_str());
				operation(curveid, dimension, R, info->curvePoints , info->noofPointsInCurve , HashArray, details, v);
				getline(myfile, nextLineOfFile);
			}
		}
		else { // is Query File
			string nextLineOfFile;
		//	while(!myfile.eof() && nextLineOfFile.compare("\n")){
				nextLineOfFile =readQueryFileLineByLine(&myfile);
		//		cout << nextLineOfFile << endl;
		//	}
		//	QueryOperation(&myfile, curveid, dimension, R, info->curvePoints , info->noofPointsInCurve , HashArray, details, v);
		}

		return nullptr;
}
