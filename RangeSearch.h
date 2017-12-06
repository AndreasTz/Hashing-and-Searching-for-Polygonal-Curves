#ifndef RANGESEARCH__H
#define RANGESEARCH__H

#include <vector>
#include "Hashing.h"
#include "Team.h"
#include "GlobalClasses.h"

using namespace std;

void RangeSearch(vector<vector<vector<long double> > >& centroids, vector<vector<vector<long double> > >& secBestCentroids, vector<vector<vector<long double> > >& AllCurves, Team * TeamArray, Team* secBestTeamArray, int noofGridCurves, int noofHTs, int type, string metric, HashMap** HashArray, vector<FrechetValues>& Fds);

long double findInitialRange(vector<vector<vector<long double> > >& centroids);
void ExhaustiveSearch(long double Range,string type, vector<long double>& centroid, const vector<vector<long double> > & curveX);


template <typename T>
int findElemInVec(const vector<long double>& toFind, vector<T>& HA);

template <class T>
static bool compareVectors(vector<T> & a, const vector<T> & b);

#endif
