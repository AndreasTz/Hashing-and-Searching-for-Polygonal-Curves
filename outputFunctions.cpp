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


void writingToOutputFile(string Filename, vector<queryDetails>& queryOfVec, vector<stats> vecOfStats ,PreferedDetails &details) {
  	ofstream file(Filename, ios_base::app | ios_base::out);
 	//	static int i= 0;

		if(!details.optionalStatsIsHere){
      for(unsigned i = 0 ; i  < queryOfVec.size() ; i++ ){
        file << "Query: " << queryOfVec[i].queryID << endl;
        file << "DistanceFunction: " << details.typeOfFunctionChoice << endl;
        file << "HashFunction: " << details.typeOfHashChoice << endl;

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
		}
		else{
      double tLSHmax = 0.0;
      double tLSHmin = 0.0;
      float tLSHavg = 0.0;
      float diffDistance = 0.0;
      float LSHminDist = 0.0;
      float LSHmaxDist = 0.0;
      float LSHavgDist = 0.0;


      for(unsigned j = 0 ; j < queryOfVec.size() ;j++){
        file << "Query: " << queryOfVec[j].queryID << endl;
        file << "DistanceFunction: " << details.typeOfFunctionChoice << endl;
        file << "HashFunction: " << details.typeOfHashChoice << endl;

        tLSHmax = *max_element(vecOfStats[j].LSHTime.begin(), vecOfStats[j].LSHTime.end());
        cout<< "Max value: " << tLSHmax <<endl;

        tLSHmin = *min_element(vecOfStats[j].LSHTime.begin(), vecOfStats[j].LSHTime.end());
        cout<< "Min value: " << tLSHmin <<endl;

        tLSHavg = accumulate( vecOfStats[j].LSHTime.begin(), vecOfStats[j].LSHTime.end(), 0.0)/ vecOfStats[j].LSHTime.size();
        cout<< "Avg value: " << tLSHavg <<endl;

        file << "tLSHmin: " << tLSHmin << endl; //min
        file << "tLSHmax: " << tLSHmax << endl; //max
        file << "tLSHavg: " << tLSHavg << endl; //avg

        LSHminDist = *min_element(vecOfStats[j].LSHDistance.begin(), vecOfStats[j].LSHDistance.end());
        cout<< "Min value: " << LSHminDist <<endl;
        LSHmaxDist = *max_element(vecOfStats[j].LSHDistance.begin(), vecOfStats[j].LSHDistance.end());
        cout<< "Max value: " << LSHmaxDist <<endl;
        LSHavgDist = accumulate( vecOfStats[j].LSHDistance.begin(), vecOfStats[j].LSHDistance.end(), 0.0)/ vecOfStats[j].LSHDistance.size();
        cout<< "Avg value: " << LSHavgDist <<endl;


        file << "|minDistanceLSH – distanceTrue|: " << abs(LSHminDist - queryOfVec[j].trueDistance) << endl; //min
        file << "|maxDistanceLSH – distanceTrue|: " << abs(LSHmaxDist - queryOfVec[j].trueDistance) << endl; //max
        file << "|avgDistanceLSH – distanceTrue|: " << abs(LSHavgDist- queryOfVec[j].trueDistance) << endl; //avg

        file << "tTrue: " << vecOfStats[j].tTime << endl;
        file << endl << endl;
      }
		}

		file.close();

}
