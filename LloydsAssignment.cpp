#include <iostream>
#include <limits>
#include <algorithm>
#include "Frechet.h"
#include "LloydsAssignment.h"

using namespace std;


void SimplestAssignment(vector<vector<vector<long double>>>& allCurves, vector<vector<vector<long double>>>& centroids,
   vector<vector<vector<long double>>>& secBestCentroids, Team* TeamArray, Team* secBestTeamArray, vector<FrechetValues>& Fds){

  int secCentroidID;
  int centroidId =0 ;
  long double minDistance;
  long double Elem;

  /*Ola ta clusters epanaprosdiorizontai me midenikous geitones :: auto simainei kai kanourioi geitones*/
  for(unsigned j = 0 ; j < centroids.size(); j++){
    TeamArray[j].members.clear();
    TeamArray[j].SetCentroidID(j);
    TeamArray[j].Centroid = centroids[j];
  }

  for(unsigned j = 0 ; j < secBestCentroids.size(); j++){
    secBestTeamArray[j].members.clear();
    secBestTeamArray[j].SetCentroidID(j);
    secBestTeamArray[j].Centroid = secBestCentroids[j];
  }
  //int th = 0;
  for(unsigned i = 0 ; i < allCurves.size(); i++)
  {
    minDistance = std::numeric_limits<long double>::infinity();
    secCentroidID = 0;
    for(unsigned j = 0 ; j < centroids.size(); j++) //briskei to kentroeides me tin mikroteri apostasi
    {
      Elem = FrechetDistance(allCurves[i], centroids[j]);
      /*if((th = Utils::findElemInVec2(allCurves[i], centroids[j], Fds))!=-1){
        Elem = Fds[th].FrechetDistance;
      }
      else{
        //cout << Fds.size() << endl;
        Elem = FrechetDistance(allCurves[i], centroids[j]);
        Fds.push_back(FrechetValues());
        Fds[Fds.size()-1].CurveI = allCurves[i];
        Fds[Fds.size()-1].CurveJ = centroids[j];
        Fds[Fds.size()-1].FrechetDistance = Elem;
      }*/

      if (minDistance > Elem)
      {
        minDistance = Elem;

        secCentroidID = centroidId;
        centroidId = j;
      }

    }

    TeamArray[centroidId].members.push_back(allCurves[i]);
    secBestTeamArray[secCentroidID].members.push_back(allCurves[i]);
  }

}
