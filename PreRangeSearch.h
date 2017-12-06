#ifndef RANGESEARCH__H
#define RANGESEARCH__H

#include "GlobalClasses.h"
#include "Hashing.h"

void addtoR(vector<int>& v, int d);
int FindHashValue(const vector<long double>& concVector);
void PreRangeSearch(Curve& curve, int noofHTs , int noofGridCurves, HashMap** HTArray, int type);
void removeDuplicates(vector<vector<long double > >& curvePoints, int dimension, int& noofPointsInCurve);
void selectDisplacedFactor(vector<double>& t, double lenOfVec);
long double selectUniformlyRandom(long double maxValue);
int ProbabilisticFindHashValue(vector<vector<long double> >& concVector);
void createVecFunc(vector<vector<long double> >& all_K_gridCurvesVecNoDublicates, vector<long double>& singleHashFuncVec);
long double selectFromNormalDistr() ;
void makeKgridCurves(int noofGridCurves, vector<vector<long double> >& Curve, vector<long double>& concatVec);
long double multiplyVectors(vector<vector<long double> >& vec1, vector<vector<long double> >& vec2);
#endif
