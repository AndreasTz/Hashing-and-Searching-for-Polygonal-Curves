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


/*Sunartisi pou upologizei tin DTW apostasi me vasi ton dothenta algorithmo
  input: 2 simeia pou dinontai san vectors
  output: -
*/
double DTWDistance(vector<double>* vec1 , vector<double>* vec2){

  //initialize DTW Array
  double **dtwArr = new double* [vec1->size()+1];
  for(int i = 0 ; i <= vec1->size(); i++){
    dtwArr[i] = new double [vec2->size()+1];
  }
  dtwArr[0][0] = 0.0;
  for(int i = 1; i < vec1->size(); i++){
    dtwArr[i][0] = numeric_limits<double>::infinity();
  }
  for(int i = 1; i < vec2->size(); i++){
    dtwArr[0][i] = numeric_limits<double>::infinity();
  }

  double cost;
  double minValue;
  //Fill Array
  for(int i = 1; i <= vec1->size(); i++){
    for(int j = 1; j <= vec2->size(); j++){
      cost= vec1[0][i] - vec2[0][j];
      if(cost < 0){
        cost= cost *(-1.0);
      }
      minValue = FindMinValue(dtwArr[i-1][j], dtwArr[i][j-1], dtwArr[i-1][j-1]);
      dtwArr[i][j] = cost + minValue  ;
    }
  }
  //Return Distance
  return dtwArr[(int)vec1->size()][(int)vec2->size()];
}
