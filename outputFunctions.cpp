#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "outputFunctions.h"

using namespace std;


void OrderNNResult(vector<string>& vec){

  for(unsigned i = 0 ; i < vec.size() -1; i++){
  //  for(unsigned j = 0 ; j < vec[i].NNcurves.size() -1; j++){

      if(vec[i] > vec[i+1]) {
        vec[i].swap(vec[i+1]);

      }
  //  }
  }
}


void writingToOutputFile(string Filename, vector<queryDetails>& queryOfVec, vector<stats>& vecOfStats ,PreferedDetails &details) {
  	ofstream file(Filename, ios_base::app | ios_base::out);
 		static int i= 0;

  	file << "Query: " << queryOfVec[i].queryID << endl;
		file << "DistanceFunction: " << details.typeOfFunctionChoice << endl;
 		file << "HashFunction: " << details.typeOfHashChoice << endl;

		if(details.optionalStatsIsHere == 0){
      if(queryOfVec[i].foundGridCurve == 0){
			     file << "Found GridCurve: " << "FALSE" << endl;
      }
      else{
          file << "Found GridCurve: " << "TRUE" << endl;
      }
			file <<	"LSH Nearest neighbor: " << queryOfVec[i].LSHNearestNeighbor << endl;
			file << "True Nearest neighbor: " << queryOfVec[i].trueNearestNeighbor << endl;
			file << "distanceLSH: " << queryOfVec[i].LSHDistance << endl;
			file << "distanceTrue: " << queryOfVec[i].trueDistance << endl;

			file << "R-near neighbors: " << endl;
      if(queryOfVec[i].NNcurves.size()){
			   OrderNNResult(queryOfVec[i].NNcurves);

         for(unsigned j = 0; j < queryOfVec[i].NNcurves.size() ; j++){
           file << queryOfVec[i].NNcurves[j] << endl;
         }
      }
      else{
        file << "[ ]" << endl;
      }

		}
		else{
      double tLSHmax;
      double tLSHmin;
      float tLSHavg ;
      for(int j = 0 ; j < vecOfStats.size() ;j++){
       tLSHmax = *max_element(vecOfStats[j].LSHTime.begin(), vecOfStats[j].LSHTime.end());
      cout<< "Max value: " << tLSHmax <<endl;

       tLSHmin = *min_element(vecOfStats[j].LSHTime.begin(), vecOfStats[j].LSHTime.end());
      cout<< "Min value: " << tLSHmin <<endl;

      tLSHavg = accumulate( vecOfStats[j].LSHTime.begin(), vecOfStats[j].LSHTime.end(), 0.0)/ vecOfStats[j].LSHTime.size();
      cout<< "Avg value: " << tLSHavg <<endl;
      }

  //    file << "|minDistanceLSH – distanceTrue|: " << vecOfStats[i].LSHDist << endl; //min
 	//		file << "|maxDistanceLSH – distanceTrue|: " << vecOfStats[i].LSHDist << endl; //max
//			file << "|avgDistanceLSH – distanceTrue|: " << vecOfStats[i].LSHDist << endl; //avg
			file << "tLSHmin: " << tLSHmin << endl; //min
			file << "tLSHmax: " << tLSHmax << endl; //max
			file << "tLSHavg: " << tLSHavg << endl; //avg
	//		file << "tTrue: " << vecOfStats[i].tTime << endl;
		}

    file << endl << endl;
		file.close();

		i++;

}
