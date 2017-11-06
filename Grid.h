#ifndef GRID__H
#define GRID__H

#include "Hashing.h"
#include "HelpClasses.h"
#include <vector>

extern vector<double> LSHTime;

void ExhaustiveSearch(vector<vector<double>>& curveVector, vector<string>& nameVector, vector<double>& qVector, queryDetails& QD, int d);

void TargettedSearch(vector<vector<double>>& curveVector, vector<string>& nameVector, vector<double>& all_K_gridCurvesVecNoDublicates, queryDetails& QD, vector<int>& IDmatchVector, int d);

void ExhaustiveSearchDTW(vector<vector<double>>& curveVector, vector<string>& nameVector, vector<double>& qVector, queryDetails& QD, int d);

void TargettedSearchDTW(vector<vector<double>>& curveVector, vector<string>& nameVector, vector<double>& all_K_gridCurvesVecNoDublicates, queryDetails& QD, vector<int>& IDmatchVector, int d);

bool CompareVectors(const vector<double>& v1, const vector<double>& v2);

bool CompareHashElementVectors(const Element& ele1, const Element& ele2);

void addtoR(vector<int>& v, int d);

void deleteR(vector<int>* v);

int FindHashValue(const vector<double>& concVector);

double selectFromNormalDistr();

double selectUniformlyRandomT(int maxValue);

double findMinPointInAnyAxis(double dimension, int axis, double curvePoint, const vector<vector<double>>& displacedGrid);

void  printGrid(const string& typeOfGrid, int noofRows ,int noofCols ,double ** printableGrid);

void removeDuplicates(vector<double>& vecWithoutDublicates, vector<vector<double>>& newCurvePoints, double dimension ,int& noofPointsInCurve);

void Operation(int flag, int curve_id, double dimension, HashMap ** const HashArray, const PreferedDetails& details, vector<double>& initialCurveNoDublicatesVec, int noofPointsInCurve, std::vector<std::vector<double>>& curvePoints, int type, vector<queryDetails>& queryOfVector, vector<vector<double>>& gridCurve, vector<string>& nameVector);
//void QOperation(double dimension, vector<double> *initialCurveNoDublicatesVec ,PreferedDetails * const details,double ** curvePoints , int noofPointsInCurve);

void printVector(const vector<double>& t);

void Concatenation(vector<double>& singleVec, vector<double>& resultVec);

void selectT_Vector(vector<double>& t, double lenOfVec);

void createVecFunc(vector<double>& all_K_gridCurvesVecNoDublicates, vector<double>& singleHashFuncVec);

void createInitialCurveNoDublicates(int dimension, vector<vector<double>>& curvePoints, int noofPointsInCurve, vector<vector<double>>& v, vector<double>& initialCurveNoDublicatesVec);

//void findPoint(int dimension, vector<double>& resultVec, vector<double>& all_K_gridCurvesVecNoDublicatesCP);

double findMinA(int dimension, int row ,int col, vector<vector <double> >& displacedFactor, const vector<double>& initialCurveNoDublicatesVec);

void fillGrid(int dimension, int noofPointsInCurve, int numberOfLocalitySensitiveFunctions, vector< vector<double> >& vectorOfVectors ,vector<double>& initialCurveNoDublicatesVec, vector<vector<double>>& Grid);

void PrepareForLSH(double dimension,
                   vector<double>& all_K_gridCurvesVecNoDublicates,
                   vector<double>& initialCurveNoDublicatesVec,
                   const PreferedDetails& details,
                   double** curvePoints,
                   int noofPointsInCurve);

//HashEntry* QueryOperation(double dimension, vector<double> *all_K_gridCurvesVecNoDublicates, vector<double> *initialCurveNoDublicatesVec ,PreferedDetails * const details, vector<vector<double>>* v, double ** curvePoints , int noofPointsInCurve);

double multiplyVectors(const vector<double>& vec1, vector<double>& vec2);

#endif
