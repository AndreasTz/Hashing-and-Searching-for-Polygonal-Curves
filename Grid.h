#ifndef GRID__H
#define GRID__H

#include "Hashing.h"
#include "HelpClasses.h"
#include <vector>

int selectUniformlyRandomT(int dimension);

double findMinPointInAnyAxis(int dimension, int axis, double curvePoint, double ** displacedGrid);

void printGrid(string typeOfGrid, int noofRows ,int noofCols ,double ** printableGrid);

void removeDuplicates(vector<double>* vecWithoutDublicates, double **newCurvePoints, int dimension ,int noofPointsInCurve);

void operation(double dimension, int R, double ** curvePoints , int noofPointsInCurve , HashMap ** const HashArray, PreferedDetails * const details);

void printVector(vector<double>* t);

void concatAnotherGridCurve(vector<double> *singleVecNoDublicates, vector<double> * all_K_gridCurvesVecNoDublicates);

void selectT_Vector(vector<double>* t, int dimension);

#endif
