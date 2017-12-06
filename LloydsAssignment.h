#ifndef LLOYDSASSIGNMENT__H
#define LLOYDSASSIGNMENT__H

#include <vector>

#include "Team.h"
#include "GlobalClasses.h"

using namespace std;

void SimplestAssignment(vector<vector<vector<long double> > >& allCurves, vector<vector<vector<long double> > >& centroids, vector<vector<vector<long double> > >& secBestCentroids, Team* TeamArray, Team* secBestTeamArray ,vector<FrechetValues>& Fds);

#endif
