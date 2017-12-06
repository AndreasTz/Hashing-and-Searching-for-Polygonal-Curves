#ifndef FRECHET__H
#define FRECHET__H

#include <vector>

using namespace std;

long double PointDistance (vector<vector<long double> >& v1, vector<vector<long double> >& v2, int point1, int point2);
long double FrechetDistance(vector<vector<long double> > & v1 , vector<vector<long double> > & v2);

long double FrechetDistanceFromID(vector<long double>& v1, const vector<long double>& v2, int d);
long double PointDistanceFromID(vector<long double>& v1, const vector<long double>& v2, int point1, int point2, int d);

bool isNull(vector<vector<long double> >& v1);
vector<long double> addMean(vector<vector<long double> >& v1, vector<vector<long double> >& v2, int point1, int point2);
vector<vector<long double> > MDFD(vector<vector<long double> >& v1, vector<vector<long double> >& v2);
vector<vector<long double> > MDFDN(vector<vector<vector<long double> > >& cluster);

long double FindMinValue(long double x1, long double x2, long double x3);
long double DTWDistanceFromID(vector<long double>& vec1, const vector<long double>& vec2);

#endif
