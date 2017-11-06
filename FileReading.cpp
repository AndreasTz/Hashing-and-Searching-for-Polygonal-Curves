#include <iostream>
#include <fstream>

#include "Grid.h"
#include "outputFunctions.h"
#include "FileReading.h"

using namespace std;

double R, dimension;

/*
Sunartisi i opoia upologizei ta vasika stixeia tis kampilis
sumfwna me to dothen input arxeio gia mia sygkekrimeni grammi
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

		}
	}
}

/*Sunartisi i opoia upologizei to eidos toy arxeiou
Returns 1: an einai input arxeio
Returns 2: an einai query arxeio*/
int DetermineTypeOfFile(ifstream* myfile){

	string firstLineOfFile ;
	getline(*myfile, firstLineOfFile);
	cout << firstLineOfFile << endl;
	string typeofFileStr = firstLineOfFile.substr (0,2);
	cout << typeofFileStr << endl;
	string defaultForInputFile = "@d";
	string defaultForQueryFile = "R:";

	if(!typeofFileStr.compare(defaultForInputFile)){
		cout << "Input File" << endl;
		R = 1.0;
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
				 kai voithitikoi vectors oi opoioi exoun dimiourgithei gia na epistrefoun sti main ta stoixeia twn kampilwn pou diavastikan
	output: -
*/
void readingFromFile(int flagBasicFuncCall, string Filename, HashMap ** const HashArray,
	PreferedDetails& details, vector<vector<double>>& v, vector<string>& nameVector,
	vector<queryDetails>& queryOfVector){

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

		static int searchingTimes = 0 ;

		clock_t begin;
		clock_t end;
		statsVec.push_back(stats());

    while(!myfile.eof() && nextLineOfFile.compare("\n")){

        EstimateCurveDetails(info, nextLineOfFile, curveNoOfPointsVec);

        int curveid = atoi(info.curve_id.c_str());
        initialCurveNoDublicatesVec.clear();

        createInitialCurveNoDublicates(dimension, info.curvePoints, info.noofPointsInCurve, v, initialCurveNoDublicatesVec);
        nameVector.push_back(info.curve_id);

        if(type == 1){ // is Input File
            Operation(flagBasicFuncCall, curveid, dimension, HashArray, details, initialCurveNoDublicatesVec, info.noofPointsInCurve , info.curvePoints , 1, queryOfVector, v, nameVector);
						flagBasicFuncCall = 1;
		    }
        else{
					if(flagBasicFuncCall == 0 ){
						searchingTimes = 0;
					}

          queryOfVector.push_back(queryDetails());
          queryOfVector[count].queryID = info.curve_id;
					if(details.optionalStatsIsHere)
						begin = clock();

          Operation(flagBasicFuncCall, curveid, dimension, HashArray, details, initialCurveNoDublicatesVec, info.noofPointsInCurve , info.curvePoints , 2, queryOfVector, v, nameVector);
					flagBasicFuncCall = 1;

					if(details.optionalStatsIsHere){
						end = clock();
						double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
						statsVec[searchingTimes].LSHTime.push_back(elapsed_secs);
						statsVec[searchingTimes].LSHDistance.push_back(queryOfVector[searchingTimes].LSHDistance);
						statsVec[searchingTimes].tTime = queryOfVector[searchingTimes].tTime;
						searchingTimes++;
					}
		    }

        getline(myfile, nextLineOfFile);

        count++;
    }

		//initialCurveNoDublicatesVec.clear();
		//curveNoOfPointsVec.clear();
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
