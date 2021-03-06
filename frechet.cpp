#include <iostream>
#include <cmath>
#include <vector>

//Calculating distance of 2 points in d-dimension space
//input: 2 vectors, the points in order you want to calculate the distance from, the dimensions of space
//output: hopefully the distance of the 2 points
using namespace std;

double PointDistance(const vector<double>& v1, const vector<double>& v2, int point1, int point2, int d)
{
	double distance = 0;
	double sum = 0;
	for (int i = point1 * d; i < point1*d+d; i++)
	{
	    sum += pow(v1[i] - v2[point2 * d + i], 2);
	}

    distance = sqrt(sum);
	return distance;
}

double FrechetDistance(const vector<double>& v1, const vector<double>& v2, int d)
{
    vector<vector<double>> C(v1.size(), vector<double>(v2.size()));
    //Initialize
    C[0][0] = PointDistance(v1, v2, 0, 0, d);
    //Dynamic Filling the n*m double array
    for (unsigned i = 0; i < v1.size(); i++)
    {
        for (unsigned j = 0; j < v2.size(); j++)
        {
            if (i == 0 && j == 0) continue;
            if (i == 0) C[0][j] = max(C[0][j-1], PointDistance(v1, v2, 0, j, d));
            else if (j == 0) C[i][0] = max(C[i-1][0], PointDistance(v1, v2, i, 0, d));
            else
            {
                double temp = min(C[i-1][j], C[i-1][j-1]);
                C[i][j] = max(min(temp, C[i][j-1]), PointDistance(v1, v2, i, j, d));
            }
        }
    }

    return C[v1.size()-1][v2.size()-1];
}
