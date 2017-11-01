#ifndef FILEREADING__H
#define FILEREADING__H

#include "Hashing.h"
#include "HelpClasses.h"
#include <cstring>

extern double R;
extern double dimension;

extern vector<stats> statsVec;

struct InitialCurve{
	    string curve_id;
	    int noofPointsInCurve;
	    std::vector<std::vector<double>> curvePoints;
};

void readingFromFile(string Filename, HashMap ** const HashArray, const PreferedDetails& details, vector<vector<double>>& v, vector<string>& nameVector, vector<queryDetails>& queryOfVector);
void EstimateCurveDetails(InitialCurve& info, string nextLineOfFile, vector<int>& curveNoOfPointsVec);
int DetermineTypeOfFile(ifstream* myfile);
string readQueryFileLineByLine(ifstream *myfile);


#endif
