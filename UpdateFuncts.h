#ifndef UPDATEFUNCTS__H
#define UPDATEFUNCTS__H

#include "Team.h"
#include "GlobalClasses.h"

class HelpStruct{
public:
  vector<vector<long double> > ObjFunctionElem;
  double ObjRes;

  void SetObjFuncElem(vector < vector <long double> > & ObjFunctionElem){
    this->ObjFunctionElem = ObjFunctionElem;
  }
  vector < vector<long double> >& GetObjFuncElem(){
    return this->ObjFunctionElem;
  }

  void SetObjRes(double ObjRes){
    this->ObjRes = ObjRes;
  }
  double GetObjRes(){
    return this->ObjRes;
  }

};

int FindOptimalCentroidFDFDN(int number_of_clusters, vector<vector<vector<long double> > >& allCurves, vector<vector<vector<long double> > >& centroids, vector<vector<vector<long double> > >& secondMinCentroids, Team * TeamArray);

int PAM_algorithm(vector<vector<vector<long double> > >& allCurves, vector<vector<vector<long double> > >& centroids, vector<vector<vector<long double> > >& secondMinCentroids, Team * TeamElem, Team * secBestTeamArray, vector<FrechetValues>& Fds);
int findObjFunction(vector< vector<long double> >& centroids, Team *TeamArray, vector<FrechetValues>& Fds);

#endif
