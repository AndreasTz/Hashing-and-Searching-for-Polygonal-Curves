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
void EstimateCurveDetails(InitialCurve& info, string nextLineOfFile, vector<int>& curveNoOfPointsVec){

	info.curve_id = strtok ( const_cast<char*> (nextLineOfFile.c_str()),"\t, ");
	string noofPointsInCurveStr =  strtok( 0 , "\t, ");
	info.noofPointsInCurve = atoi(noofPointsInCurveStr.c_str());
	curveNoOfPointsVec.push_back(info.noofPointsInCurve);
	string pointStr;

    info.curvePoints = std::vector<std::vector<double>>(info.noofPointsInCurve, std::vector<double>((int)dimension));

	for(int i = 0; i < info.noofPointsInCurve ; i++){
		for(int j = 0 ; j < (int)dimension ; j++){

			pointStr = strtok (  0 ,"()\t, ");
			info.curvePoints[i][j] = stof(pointStr);
			// cout << info -> curvePoints[i][j] << " " << endl;

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

		R = atof(Rstr.c_str());

		return 2;
	}
    throw;
}


/*
Synartisi i opoia diavazei to input arxeio kai ektelei ton algorithmo gia mia mia kampili
	input: Filename (onoma arxeiou)
				 HashArray (Pinakas me deiktes se HashTables)
				 details (stoixeia voithitikis klasis gia ta arxika stoixeia pou prostithentai)
	output: -

*/
void readingFromFile(string Filename, HashMap ** const HashArray, const PreferedDetails& details, vector<vector<double>>& v, vector<string>& nameVector, vector<queryDetails>& queryOfVector){

    ifstream myfile;
    myfile.open(Filename);
    if(!myfile.good()){
        cerr << " Problem in openning the file you've asked " << endl;
        exit(-2);
    }

    InitialCurve info;
    int type = DetermineTypeOfFile(&myfile);

    vector<int> curveNoOfPointsVec;

    string nextLineOfFile ;
    getline(myfile, nextLineOfFile);

    vector<double> initialCurveNoDublicatesVec;
    int count = 0;
    while(!myfile.eof() && nextLineOfFile.compare("\n")){

        EstimateCurveDetails(info, nextLineOfFile, curveNoOfPointsVec);

        int curveid = atoi(info.curve_id.c_str());
        initialCurveNoDublicatesVec.clear();
        createInitialCurveNoDublicates(dimension, info.curvePoints, info.noofPointsInCurve, v, initialCurveNoDublicatesVec);
        nameVector.push_back(info.curve_id);
        if(type == 1){ // is Input File

            Operation(curveid, dimension, HashArray, details, initialCurveNoDublicatesVec, info.noofPointsInCurve , info.curvePoints , 1, queryOfVector, v, nameVector);
        }
        else{

            queryOfVector.push_back(queryDetails());
            queryOfVector[count].queryID = info.curve_id;

            Operation(curveid, dimension, HashArray, details, initialCurveNoDublicatesVec, info.noofPointsInCurve , info.curvePoints , 2, queryOfVector, v, nameVector);
        }
        getline(myfile, nextLineOfFile);
        count++;
    }
}


/*Sunartisi pou diavazei mia- mia tin grammi enos queryFile*/
string readQueryFileLineByLine(ifstream *myfile){
	string Line;
	getline(*myfile, Line);
	if(!myfile->eof() && Line.compare("\n")){

		vector<int> curveNoOfPointsVec;
		InitialCurve info;

		EstimateCurveDetails(info, Line, curveNoOfPointsVec);

		return Line;
	}
    throw;
}
