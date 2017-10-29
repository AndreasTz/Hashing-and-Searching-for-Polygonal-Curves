#ifndef FRECHET__H
#define FRECHET__H

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double PointDistance(const vector<double>& v1, const vector<double>& v2, int point1, int point2, int d);

double FrechetDistance(const vector<double>& v1, const vector<double>& v2, int d);

#endif
