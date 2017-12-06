#ifndef OUTPUFUNCS__H
#define OUTPUFUNCS__H

#include <string>
#include "Team.h"


int EstimateSilhouette(int number_of_clusters, vector<vector<vector<long double> > >& centroids, vector<vector<vector<long double> > >& allCurves, vector<long double>& s, Team* TeamArray, Team * secBestTeamArray, vector<vector<vector<long double> > >& secBestCentroids );
void PrintResults(string FileName, vector<vector<vector<long double> > >& AllCurves, int number_of_clusters, string TypeOfAssignment, string TypeOfInit, string TypeOfUpdate, string TypeOfMetric, Team* TeamArray , int CompleteParamIShere,long double clusteringTime, vector<long double>& s, vector<string>& nameVector);


#endif
