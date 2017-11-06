#ifndef DTW__H
#define DTW__H

#include <vector>

double FindMinValue(double x1, double x2, double x3);

void findPoint(int dimension, std::vector<double> all_K_gridCurvesVecNoDublicatesCP, std::vector<double>& resultVec);

double DTWDistance(std::vector<double>& vec1, std::vector<double>& vec2);

#endif
