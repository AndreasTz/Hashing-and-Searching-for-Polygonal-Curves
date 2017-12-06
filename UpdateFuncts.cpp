#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

#include "Frechet.h"
#include "UpdateFuncts.h"
#include "VectorUtils.h"
#include "RangeSearch.h"

using namespace std;


int FindOptimalCentroidFDFDN(int number_of_clusters, vector<vector<vector<long double>>>& allCurves, vector<vector<vector<long double>>>& centroids, vector<vector<vector<long double>>>& secondMinCentroids, Team * TeamArray)
{
	vector<vector<vector<long double>>> centroidCP(centroids);
	centroids.clear();
	secondMinCentroids.clear();

	vector<vector<vector<long double>>>::iterator it;
	vector<vector<long double>> optimalCentroid;

	long double minDist;
	int ID;
	int secID;
	long double temp;

	for (int i = 0; i < number_of_clusters; ++i)
	{
		optimalCentroid = MDFDN(TeamArray[i].members);

		//to kalytero ketroeides einai ayto pou einai pio konta sto optimalCentroid.
		minDist = std::numeric_limits<long double>::infinity();
		ID = 0;
		secID = 0;

		for (unsigned j = 0; j < TeamArray[i].members.size(); ++j)
		{
			temp = FrechetDistance(optimalCentroid, TeamArray[i].members[j]);
			if (temp < minDist)
			{
				secID = ID;
				if((it= find(allCurves.begin(), allCurves.end(), TeamArray[i].members[j])) != allCurves.end()){
					ID = distance(allCurves.begin(), it);
				}
				//cout << "ID: " << ID << endl;
				minDist = temp;
			}
		}
		if (FrechetDistance(centroidCP[i], optimalCentroid) < minDist)
		{
			return 0;
		}
		secondMinCentroids.push_back(allCurves[secID]);
		centroids.push_back(allCurves[ID]) ;
	}
	return 1;
}


int findObjFunction(vector< vector<long double> > & centroids, Team& TeamElem, vector<FrechetValues>& Fds){

  long double sum = 0.0;
	//int th = 0;

  for(unsigned j = 0 ; j < TeamElem.members.size() ; j++)
  {

    sum+= FrechetDistance(TeamElem.members[j], centroids);
	/*	if((th = Utils::findElemInVec2(TeamElem.members[j], centroids, Fds)) > 0){
			sum+= Fds[th].FrechetDistance;
		}
		else{
			long double Elem = FrechetDistance(TeamElem.members[j], centroids);
			sum+= Elem;
			Fds.push_back(FrechetValues());
			Fds[Fds.size() -1 ].CurveI = TeamElem.members[j];
			Fds[Fds.size() -1 ].CurveJ = centroids;
			Fds[Fds.size() -1 ].FrechetDistance = Elem;
		}*/
    //sum+=rand();
  }

  return sum;
}


int PAM_algorithm(vector<vector<vector<long double>>>& allCurves, vector<vector<vector<long double>>>& centroids,
	vector<vector<vector<long double>>>& secondMinCentroids, Team * TeamArray, Team* secBestTeamArray, vector<FrechetValues>& Fds){

  int position;
  int positionOf2nd;
  int updated = 1;

  vector<vector<vector<long double>>> centroidCP(centroids);
	vector<vector<long double>> SinglecentroidCP;
  vector<long double> ObjFuncRes;


	centroids.clear();
	secondMinCentroids.clear();

  for(unsigned i = 0 ; i < centroidCP.size() ; i++ )
  {
		SinglecentroidCP = centroidCP[i];
    for(unsigned j = 0; j < TeamArray[i].members.size(); j++)
    {

      swap(centroidCP[i] , TeamArray[i].members[j]);

      ObjFuncRes.push_back(findObjFunction(centroidCP[i], TeamArray[i], Fds));

    }

		if(TeamArray[i].members.size())
    {
      position = distance(ObjFuncRes.begin(), min_element(ObjFuncRes.begin(), ObjFuncRes.end()));
      ObjFuncRes.erase(ObjFuncRes.begin()+position);
      positionOf2nd = distance(ObjFuncRes.begin(), min_element(ObjFuncRes.begin(), ObjFuncRes.end()));

			centroids.push_back(allCurves[position]);
      secondMinCentroids.push_back(allCurves[positionOf2nd]);

	  //	TeamArray[i].Centroid.clear();
    //  TeamArray[i].Centroid(TeamArray[i].members[position]);
		//	secBestTeamArray[i].Centroid.clear();
		//	secBestTeamArray[i].Centroid = secBestTeamArray[i].members[position];
      if(Utils::compareVectors(centroids[centroids.size()-1],SinglecentroidCP)  == true ){
        updated = 0;
      }
  //    TeamArray[i].SetCentroidID(position);
  //    TeamArray[i].members.clear(); //Tha gemisei sto assignment
    }
  }

  return (updated);
}
