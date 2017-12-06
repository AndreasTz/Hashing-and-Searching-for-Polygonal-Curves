#include <iostream>
#include <algorithm>
#include <fstream>
#include "VectorUtils.h"
#include "outputFuncs.h"
#include "Frechet.h"



using namespace std;
using namespace Utils;


int EstimateSilhouette(int number_of_clusters, vector<vector<vector<long double>>>& centroids, vector<vector<vector<long double>>>& allCurves, vector<long double>& s, Team* TeamArray, Team * secBestTeamArray, vector<vector<vector<long double>>>& secBestCentroids ){

  long double diff;
  long double max;
  long double avg2 = 0.0;
  long double avg1 = 0.0;
  int teamID;
  vector<vector<vector<long double>>>::iterator it;
  
  for(unsigned i =0 ; i < allCurves.size(); i++){ //an einai kentroeides

    if((it= find(centroids.begin(), centroids.end(), allCurves[i])) != centroids.end()) {
      teamID = distance(centroids.begin(), it);
      for(unsigned j = 0 ; j < TeamArray[teamID].members.size(); j++){
        avg1+= FrechetDistance(TeamArray[teamID].Centroid, TeamArray[teamID].members[j]);
      }

    }
    else { //an einai aplo simeio

      for(int k = 0 ; k  < number_of_clusters ; k++)
      {
        //bres se poia omada anikei
        if((it =find(TeamArray[k].members.begin(), TeamArray[k].members.end(), allCurves[i])) != TeamArray[k].members.end()) {
          teamID = k;
          for(unsigned j = 0 ; j < TeamArray[k].members.size(); j++){

            avg1+= FrechetDistance(TeamArray[k].Centroid, TeamArray[k].members[j]);
          }
          break;
        }
      }
    }

    avg1= avg1/(TeamArray[teamID].members.size() - 1); //-1 epeidh h mia frechet gyrnaei 0, me ton eaytou tou.

///////////////////////////////////////////////////////////////////////////////
  if((it= (find(secBestCentroids.begin(), secBestCentroids.end(), allCurves[i]))) != secBestCentroids.end()) {

    for(unsigned j = 0 ; j < secBestTeamArray[i].members.size(); j++){
      avg2+= FrechetDistance(secBestTeamArray[i].Centroid, secBestTeamArray[i].members[j]);
    }

  }
  else {

    for(int k = 0 ; k  < number_of_clusters ; k++)
    {

      if((it = find(secBestTeamArray[k].members.begin(), secBestTeamArray[k].members.end(), allCurves[i])) != secBestTeamArray[k].members.end()) {
        teamID = k;
        for(unsigned j = 0 ; j < secBestTeamArray[k].members.size(); j++){
          avg2+= FrechetDistance(secBestTeamArray[k].Centroid, secBestTeamArray[k].members[j]);
        }
        break;
      }
    }
  }

  avg2= avg2/secBestTeamArray[teamID].members.size();


  diff =  avg2- avg1;

  max = avg1;
  if(avg2 > max) { max = avg2;}

  s.push_back(diff/max);
  }


  return 0;
}


void PrintResults(string FileName, vector<vector<vector<long double>>>& AllCurves, int number_of_clusters, string TypeOfAssignment, string TypeOfInit, string TypeOfUpdate, string TypeOfMetric, Team* TeamArray, int CompleteParamIShere, long double clusteringTime, vector<long double>& s, vector<string> & nameVector){

	ofstream file(FileName, ios_base::app | ios_base::out);

  file << "Algorithm: I " << TypeOfInit << " A " << TypeOfAssignment << " U " << TypeOfUpdate << endl;
  file << "Metric: " << TypeOfMetric << endl;

  vector<vector<vector<long double>>>::iterator it;
  int th= 0;

  for(int i =0 ; i < number_of_clusters; i++){
    file << "CLUSTER: " << i <<  endl;
    file << "size: " << TeamArray[i].members.size() << endl;

    if((it= find(AllCurves.begin(), AllCurves.end(), TeamArray[i].Centroid)) != AllCurves.end()) {
      th = distance(AllCurves.begin(), it);
    }
    file << "centroid: " << nameVector[th] << endl; //na allaksw
    if(!TypeOfUpdate.compare("Frechet")){
      file << "centroids with mean Frechet: " << endl;
      printVectorOfVector(TeamArray[i].Centroid);
    }
    if(CompleteParamIShere){
      //IDs kampilwn
      for(unsigned j = 0 ; j < TeamArray[i].members.size() ; j++){
        if((it= find(AllCurves.begin(), AllCurves.end(), TeamArray[i].members[j])) != AllCurves.end()) {
          th = distance(AllCurves.begin(), it);
        }
        file << nameVector[th] << " , ";
      }
      file << endl;
    }
  }
  long double Total;

  file << "clustering_time: " << clusteringTime << endl;
  file << "Silhouette: " <<  endl;
  file << "[ ";
  for(unsigned i = 0; i < s.size(); i++)
  {
    file << s[i] << ", ";
    Total+=s[i];
  }


  file << "S_total: " << Total/s.size() << " ]" << endl;
}
