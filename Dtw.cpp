#include <iostream>
#include <vector>
#include <limits>

#include "Dtw.h"

using namespace std;


/*Synartisi pou upologizei tin elaxisti timi anamesa se 3 pragmatikous arithmous*/
double FindMinValue(double x1, double x2, double x3){
  double minV = x1;
  if(x2 < minV){
    minV = x2;
  }
  if(x3 < minV){
    minV = x3;
  }

  return(minV);
}


/*
Sunartisi i opoia apo ena vector briskei ena simeio
input : dimension(diastasi simeiou)
        resultVec (vector apothikeysis apotelesmatos)
        all_K_gridCurvesVecNoDublicatesCP (vector pou periexei kai tis k kampiles plegmatos )
output: -
*/
void findPoint(int dimension, vector<double> all_K_gridCurvesVecNoDublicatesCP, vector<double>& resultVec){
  double Elem;
  resultVec.clear();
  for(int i = 0; i < dimension ; i++){
    Elem = all_K_gridCurvesVecNoDublicatesCP.back();
    all_K_gridCurvesVecNoDublicatesCP.pop_back();
    resultVec.push_back(Elem);
  }
}


/*//vec1 :: gridCurve[i] / vec2 :: allKg
double DTWDistance(vector<double>& vec1, vector<double>& vec2, int dimension)
{
  vector<> point;

}*/


/*Sunartisi pou upologizei tin DTW apostasi me vasi ton dothenta algorithmo
  input: 2 simeia pou dinontai san vectors
  output: -
*/
double DTWDistance(vector<double>& vec1, vector<double>& vec2){

  vector<vector<double>> dtwVec(vec1.size(), vector<double>(vec2.size()));

  dtwVec[0][0] = 0.0;

  for(unsigned i = 1; i < vec1.size(); i++){
    dtwVec[i][0] = numeric_limits<double>::infinity();
  }
  for(unsigned i = 1; i < vec2.size(); i++){
    dtwVec[0][i] = numeric_limits<double>::infinity();
  }

  double cost;
  double minValue;

  for(unsigned i = 1; i <= vec1.size(); i++){
    for(unsigned j = 1; j <= vec2.size(); j++){
      cost = vec1[i] - vec2[j];
      if(cost < 0){
        cost = cost *(-1.0);
      }
      minValue = FindMinValue(dtwVec[i-1][j], dtwVec[i][j-1], dtwVec[i-1][j-1]);
      dtwVec[i][j] = cost + minValue  ;
    }
  }
  //Return Distance
  return dtwVec[(int)vec1.size()][(int)vec2.size()];
}
