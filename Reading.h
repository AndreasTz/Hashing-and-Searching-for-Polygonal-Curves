#ifndef READING__H
#define READING__H

#include "GlobalClasses.h"
#include "Hashing.h"
#include <string>


void OpenFile(ifstream& myfile, string Filename);
int EstimateDimensions(ifstream &myfile);
void EstimateCurveDetails(Curve& curve, string Line, int dimension);
int EstimateTotalLines(ifstream& myfile);
void readingFromFile(ifstream& myfile, vector<vector<vector<long double> > >& AllCurvePonts, int noofHTs, int noofGridCurves, HashMap** HTArray, int type, vector<string> & nameVector);
void readingFromCMD(int howManyArgs, char *argv[] , PreferedDetails& details) ;
void readingConfFile(string fileName, Parameters& params);
//void removeDuplicates(vector<vector<long double> >& curvePoints, int dimension, int& noofPointsInCurve);

#endif
