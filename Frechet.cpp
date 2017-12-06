#include <iostream>
#include <cmath>
#include <limits>

#include "Frechet.h"
#include "VectorUtils.h"

using namespace std;


long double PointDistance (vector<vector<long double>>& v1, vector<vector<long double>>& v2, int point1, int point2)
{
    long double distance = 0;
    long double sum = 0;
    unsigned dimension = v1[0].size();

    for (unsigned i = 0; i < dimension; ++i)
    {
        sum += pow(abs(v1[point1][i] - v2[point2][i]), 2);
    }

    distance = sqrt(sum);
    return distance;
}


long double FrechetDistance(vector<vector<long double>> & v1 , vector<vector<long double>> & v2) {

    vector<vector<long double>> C(v1.size(), vector<long double>(v2.size()));

    //Initialize
    C[0].push_back(PointDistance(v1, v2, 0, 0));

    ////cout << v1.size() << "  " << v2.size() << endl;
    //Dynamically fill the n*m long double array
    for (unsigned i = 0; i < v1.size(); i++)
    {
        for (unsigned j = 0; j < v2.size(); j++)
        {
            if (i == 0 && j == 0) continue;
            if (i == 0) C[0][j] = max(C[0][j-1], PointDistance(v1, v2, 0, j));
            else if (j == 0) C[i][0] = max(C[i-0][0], PointDistance(v1, v2, i, 0));
            else
            {
                long double temp = min(C[i-1][j], C[i-1][j-1]);
                C[i][j] = max(min(temp, C[i][j-1]), PointDistance(v1, v2, i, j));
            }
        }
    }

    ////cout << "Initialized at:: " << C[0][0] << endl;
    ////cout << "Ended at:: " << C[v1.size() - 1][v2.size() - 1] << endl;

  //  return 0;
    return C[v1.size() - 1][v2.size() - 1];
}


long double PointDistanceFromID(vector<long double>& v1,const vector<long double>& v2, int point1, int point2, int d)
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


long double FrechetDistanceFromID(vector<long double>& v1, const vector<long double>& v2, int d)
{
    vector<vector<long double>> C(v1.size(), vector<long double>(v2.size()));
    //Initialize
    C[0][0] = PointDistanceFromID(v1, v2, 0, 0, d);
    //Dynamic Filling the n*m double array
    for (unsigned i = 0; i < v1.size(); i++)
    {
        for (unsigned j = 0; j < v2.size(); j++)
        {
            if (i == 0 && j == 0) continue;
            if (i == 0) C[0][j] = max(C[0][j-1], PointDistanceFromID(v1, v2, 0, j, d));
            else if (j == 0) C[i][0] = max(C[i-1][0], PointDistanceFromID(v1, v2, i, 0, d));
            else
            {
                long double temp = min(C[i-1][j], C[i-1][j-1]);
                C[i][j] = max(min(temp, C[i][j-1]), PointDistanceFromID(v1, v2, i, j, d));
            }
        }
    }

    return C[v1.size()-1][v2.size()-1];
}


bool isNull(vector<vector<long double>>& v1)
{

	unsigned dimension = v1[0].size();

	for (unsigned i = 0; i < dimension; ++i)
	{

		if (v1[0][i] != -1) return false;
	}

	return true;

}


vector<long double> addMean(vector<vector<long double>>& v1, vector<vector<long double>>& v2, int point1, int point2)
{
    vector<long double> meanVec;
    unsigned dimension = v1[0].size();

    for (unsigned i = 0; i < dimension; ++i)
    {
        meanVec.push_back((v1[point1][i] + v2[point2][i]) / 2);
    }
    return meanVec;
}


vector<vector<long double>> MDFD(vector<vector<long double>>& v1, vector<vector<long double>>& v2)
{

  //null vector!*/
	if (isNull(v1) && isNull(v2)) return v1;
	else if(isNull(v1)) return v2;
	else if(isNull(v2)) return v1;

  vector<vector<long double>> C(v1.size(), vector<long double>(v2.size()));
	//Initialize
    C[0][0] = PointDistance(v1, v2, 0, 0);
    //Dynamically fill the n*m long double array
    for (unsigned i = 0; i < v1.size(); i++)
    {
        for (unsigned j = 0; j < v2.size(); j++)
        {
            if (i == 0 && j == 0) continue;
            if (i == 0) C[0][j] = max(C[0][j-1], PointDistance(v1, v2, 0, j));
            else if (j == 0) C[i][0] = max(C[i-0][0], PointDistance(v1, v2, i, 0));
            else
            {
                long double temp = min(C[i-1][j], C[i-1][j-1]);
                C[i][j] = max(min(temp, C[i][j-1]), PointDistance(v1, v2, i, j));
            }
        }
    }

    ////cout << "Initialized at:: " << C[0][0] << endl;
    ////cout << "Ended at:: " << C[v1.size() - 1][v2.size() - 1] << endl;
    //WE HAVE FILLED THE C-DynProg vector!

    //initializing the traversal curve!
    vector<vector<long double>> traversalCurve;
    vector<long double> tempVec;
    int pi = v1.size() - 1;
    int qj = v2.size() - 1;
    unsigned dimension = v1[0].size();
    for (unsigned i = 0; i < dimension; i++)
    {
        tempVec.push_back((v1[pi][i] + v2[qj][i]) / 2);
    }
    traversalCurve.push_back(tempVec);


    int minldx;
    while (pi != 0 && qj != 0)
    {
        if (C[pi - 1][qj] < C[pi][qj - 1] && C[pi - 1][qj] < C[pi - 1][qj - 1]) minldx = 0;
        else if (C[pi][qj - 1] < C[pi - 1][qj] && C[pi][qj - 1] < C[pi -1 ][qj - 1]) minldx = 1;
        else minldx = 2;

        if (minldx == 0) traversalCurve.push_back(addMean(v1, v2, pi -1, qj));
        else if (minldx == 1) traversalCurve.push_back(addMean(v1, v2, pi, qj - 1));
        else traversalCurve.push_back(addMean(v1, v2, pi - 1, qj - 1));

        if (pi != 0) --pi;
        if (qj != 0) --qj;
    }
    return traversalCurve; //type vector<vector<long double>>!!!!
}


vector<vector<long double>> MDFDN(vector<vector<vector<long double>>>& cluster)
{


    unsigned dimension = cluster[0][0].size();

    //vector<vector<long double>> CurveVector;

    int num;
    num = cluster.size();

    //vriskw vathos dentrou, to mhkos tou vector tha einai
	int height = 0;
	for (int h = 0; ; ++h)
	{
	    if ((num > pow(2, h)) && (num < pow(2, h + 1)))
	    {
	        height = h + 2;
	        break;
	    }
	}

	//Initialize vector-tree with zeroes!
	int vectorElements = pow(2, height) - 1;
	//vector<vector<vector<long double>>> FBTree(vectorElements, 0.0);
  vector<vector<vector<long double>>> FBTree(vectorElements, vector<vector<long double>>(0, vector<long double>(0)));

	////cout << "GIA:: " << num << " STOIXEIA VRHKA VATHOS:: " << height << endl;

	//filler vector
	vector<vector<long double>> fv;
	vector<long double> tempv;
	for (unsigned i = 0; i < dimension; ++i)
	{
		tempv.push_back(-1);
	}
	fv.push_back(tempv);

  /*vector<vector<long double>> fv;
  vector<long double> v;
  v.push_back(-0.14);
  fv.push_back(v);
  //cout << fv[0][0] << " TOSO EINAI TO FILLER!!!!" << endl;*/

  /*bool que = isNull(fv);
  //cout << "TO FV EINAI::::::::::: " << que << endl;*/

	//fill vector-tree with the curve ID's we want
	for (int i = 0; i < vectorElements; i+=2)                                         ///////////////////////////EDW PROSOXI, EINAI IDS!!! THELEI INTEGRATION!!!
	{
	    if (i / 2 >= num)
	    {
	        ////cout << "MPHKA ME i = " << i << " KAI PROSTHESA THN TIMH:: " << FBTree[i-2] << endl;
          //cout << "mphka gia th thesi:::::: " << i << endl;
	        FBTree[i] = fv;
	        //continue;
	    }
	     else FBTree[i] = cluster[i/2];
	    //if ((i+1)*2 > vectorElements) break;
	    ////cout << FBTree[i] << endl;
	}
  //FBTree[(num*2) - 2] = fv;
	//calculate row depth height - 1!
  //cout << "EXW TOSA VECTOR ELEMENTS:: " << vectorElements << endl;
  //cout << "KAI TOSA VECTOR CURVES:: " << num << endl;
	/*for (int i = 1; i + 4 < vectorElements; i+=4)                          /////////////////////////////////////////////edw epishs prepei na kaleite curveVector[FBTree[i-1], oxi sketo, giati ta fyla einai IDs!
	{
	    FBTree[i] = MDFD(FBTree[i-1], FBTree[i+1]);
      FBTree[i-1] = FBTree[i+1] = fv;
	    ////cout << FBTree[i] << endl;
	    if (i+4 > vectorElements) break;
	}*/

	//GIA n IDs OPOU n - 2^x = y, tha teleytaia y stoixeia tha arxikopoiountai me to id tou aristerou!!!!!!!!!!!

  //Utils::printVectorOfVector(FBTree[170]);

	////cout << "KASFJKASKFKJTGWKEJT " << pow(2, height) << endl;
	//Gia ola ta ypoloipa ypsh!
  int times;
	for(int h = 1; h < height; h++)
	{
	        for (int i = (pow(2, h) - 1); i < vectorElements - 1; i+= pow(2, h+1))
	        {
              times++;
              FBTree[i] = MDFD(FBTree[i - pow(2, h-1)], FBTree[i + pow(2, h-1)]);
              if (i + 4 > 255) //cout << "SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS" << endl;

	            /*int Low = i - pow(2, h-1);
	            int High = i + pow(2, h-1);
	            //cout << "KAI MPAINW STIS TIMES:: " << Low << " :: KAI :: " << High << " ::!" << endl;*/

	            ////cout << FBTree[i] << endl;
	            if (i + pow(2, h+1) > vectorElements) break;
	        }
	}

	return FBTree[vectorElements / 2];
}


long double FindMinValue(long double x1, long double x2, long double x3){
  long double minV = x1;
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
long double DTWDistanceFromID(vector<long double>& vec1, const vector<long double>& vec2){

  vector<vector<long double> > dtwVec(vec1.size(), vector<long double>(vec2.size()));

  dtwVec[0][0] = 0.0;

  for(unsigned i = 1; i < vec1.size(); i++){
    dtwVec[i][0] = numeric_limits<long double>::infinity();
  }
  for(unsigned i = 1; i < vec2.size(); i++){
    dtwVec[0][i] = numeric_limits<long double>::infinity();
  }

  long double cost;
  long double minValue;

  for(unsigned i = 1; i < vec1.size(); i++){
    for(unsigned j = 1; j < vec2.size(); j++){
      cost = vec1[i] - vec2[j];
      if(cost < 0){
        cost = cost *(-1.0);
      }
      minValue = FindMinValue(dtwVec[i-1][j], dtwVec[i][j-1], dtwVec[i-1][j-1]);
      dtwVec[i][j] = cost + minValue  ;
    }
  }
  //Return Distance
  return dtwVec[(int)vec1.size()-1][(int)vec2.size()-1];
}
