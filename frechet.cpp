#include <iostream>
#include <cmath>
#include <vector

//Calculating distance of 2 points in d-dimension space
//input: 2 vectors, the points in order you want to calculate the distance from, the dimensions of space
//output: hopefully the distance of the 2 points.

double PointDistance(vector<double>* v1, vector<double>* v2, int point1, int point2, int d)
{
	cout << "The distance of point 1 between v1 and v2 is: " << endl;
	
	double distance = 0;
	double sum = 0;
	/*for (int i = point1 * d; i < point1*d+d; i++)
	{
	    sum += pow(v1[0][i] - v2[0][i], 2);
	}*/
	
	for (int i = point1 * d; i < point1*d+d; i++)
	{
	    sum += pow(v1[0][i] - v2[0][point2 * d + i], 2);
	}
	
    distance = sqrt(sum);
    cout << distance << "****!" << endl;
	return distance;
}