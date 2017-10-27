#ifndef GRID__H
#define GRID__H

#include "Hashing.h"
#include "HelpClasses.h"
#include <vector>

int CompareVectors(vector<double>* v1, vector<double>* v2);

int CompareHashElementVectors(Element* ele1, Element* ele2);

void addtoR(vector<int>* v, int d);

void deleteR(vector<int>* v);

int FindHashValue(vector<double>* concVector);

double selectFromNormalDistr();

double selectUniformlyRandomT(int maxValue);

double findMinPointInAnyAxis(int dimension, int axis, double curvePoint, double ** displacedGrid);

void printGrid(string typeOfGrid, int noofRows ,int noofCols ,double ** printableGrid);

void removeDuplicates(vector<double>* vecWithoutDublicates, double **newCurvePoints, double dimension ,int* noofPointsInCurve);

void Operation(int curve_id, double dimension, HashMap ** const HashArray, PreferedDetails * const details, vector<double>* initialCurveNoDublicatesVec, int noofPointsInCurve, double ** curvePoints, int type, vector<queryDetails> *queryOfVector);
//void QOperation(double dimension, vector<double> *initialCurveNoDublicatesVec ,PreferedDetails * const details,double ** curvePoints , int noofPointsInCurve);

void printVector(vector<double>* t);

void Concatenation(vector<double> *singleVec, vector<double> * resultVec);

void selectT_Vector(vector<double>* t, double lenOfVec);

void createVecFunc(double dimension,vector<double>* all_K_gridCurvesVecNoDublicates, vector<double>* singleHashFuncVec);

void createInitialCurveNoDublicates(int dimension, double ** curvePoints, int noofPointsInCurve, vector<vector<double>>* v, vector<double>* initialCurveNoDublicatesVec);

void findPoint(double dimension, vector<double> *resultVec, vector<double>* all_K_gridCurvesVecNoDublicatesCP);

double findMinA(int dimension, int row ,int col, vector<vector <double> >* displacedFactor, vector<double>* initialCurveNoDublicatesVec);

void fillGrid(int dimension, int numberOfLocalitySensitiveFunctions, vector< vector<double> >* vectorOfVectors ,vector<double>* initialCurveNoDublicatesVec, double** Grid);

void PrepareForLSH(double dimension, vector<double> *all_K_gridCurvesVecNoDublicates, vector<double> *initialCurveNoDublicatesVec, PreferedDetails * const details, double ** curvePoints , int noofPointsInCurve);

HashEntry* QueryOperation(double dimension, vector<double> *all_K_gridCurvesVecNoDublicates, vector<double> *initialCurveNoDublicatesVec ,PreferedDetails * const details, vector<vector<double>>* v, double ** curvePoints , int noofPointsInCurve);

double multiplyVectors(vector<double>* vec1, vector<double>* vec2);

#endif
