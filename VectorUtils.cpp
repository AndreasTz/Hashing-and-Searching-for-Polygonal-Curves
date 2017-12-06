#include <algorithm>

#include "VectorUtils.h"

using namespace std;
using namespace Utils;


long double Utils::findMinElemFromVector(vector<long double>& distanceVec){

  long double minDistance = *min_element(distanceVec.begin(), distanceVec.end());
  //cout<< "Min distance: " << minDistance <<endl;
  return minDistance;

}


long double Utils::findMaxElemFromVector(vector<long double>& distanceVec){

  long double maxDistance = *max_element(distanceVec.begin(), distanceVec.end());
  //cout<< "Max distance: " << maxDistance <<endl;
  return maxDistance;

}
