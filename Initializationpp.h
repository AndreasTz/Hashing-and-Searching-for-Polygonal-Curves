#ifndef INITIALIZATIONPP__H
#define INITIALIZATIONPP__H
#include <vector>
#include "GlobalClasses.h"


using namespace std;

template<typename TypeX>
TypeX selectUniformlyRandom(double minValue, TypeX maxValue);

int selectRandomlyFirstCentroids(vector<vector<vector<long double> > >& all_curves);

long double estimateSum(long double minDistanceBetwPointandCentr, long double maxDistanceBetwPointandCentr);

void findNewCentroid(vector<vector<vector<long double> > >& allCurvesCP, vector<vector<vector<long double> > >& centroids);

void MainInitializationPP(vector<vector<vector<long double> > >& allCurvesCP, vector< vector<vector<long double> > >& centroids, vector<FrechetValues>& Fds);

int initializationPlusPlus(vector <vector<vector<long double> > >& all_curves, vector <vector<vector<long double> > >& centroids, vector<FrechetValues>& Fds);

void simplestInitialization(vector<vector<vector<long double> > >& allCurvesCP, vector<vector<vector<long double> > >& centroids);

#endif
