#include <iostream>
#include <cmath>
#include <algorithm>

#include "Initializationpp.h"
#include "VectorUtils.h"
#include "Frechet.h"

extern int NOOFCENTROIDS;

using namespace std;
using namespace Utils;



template<typename TypeX>
TypeX selectUniformlyRandom(double minValue, TypeX maxValue){
  TypeX min = minValue;
  TypeX max = maxValue ;
  return min + (TypeX) ((max-min+1.0) * (rand() / (RAND_MAX + 1.0)));
}


int selectRandomlyFirstCentroids(vector<vector<vector<long double>>>& all_curves){

  int maxPos = all_curves.size();
  int pos = selectUniformlyRandom(0 , maxPos - 1);

  return pos;
}



long double estimateSum(long double minDistanceBetwPointandCentr, long double maxDistanceBetwPointandCentr) {

  static double sum = 0.0 ;
  double minDistPow = pow(minDistanceBetwPointandCentr, 2);
  //sum+= (minDistPow/maxDistanceBetwPointandCentr); //kanonikopoiisi
  sum+= minDistPow;
  return sum;
}


void simplestInitialization(vector<vector<vector<long double>>>& allCurvesCP, vector<vector<vector<long double>>>& centroids){
    int position;
    cout << NOOFCENTROIDS << endl;
    for(int i = 0 ; i < NOOFCENTROIDS ; i++)
    {
      position = selectRandomlyFirstCentroids(allCurvesCP);
      centroids.push_back(allCurvesCP[position]);
      allCurvesCP.erase(allCurvesCP.begin() + position); /*afairoume ta kentroeidi :: PROSOXI ta bazw se antigrafo giati ta kentroeidi tha allaksoun*/
    }

}


void findNewCentroid(vector<vector<vector<long double>>>& allCurvesCP, vector<vector<vector<long double>>>& centroids, vector<long double>& curveP){

  int newCentroidPos = 0 ;
  long double x;
  x = selectUniformlyRandom(0.0, 100.0); //bres tyxaia ena x kai psakse se poio simeio anikei

  /*Gia kathe simeio tis diamerisis briskw se poio anikei to tyxaio x - ara poio einai to pio pithan set emfanisis tou*/
  for(unsigned r = 1; r < curveP.size(); r++)
  {

  	x -= curveP[r];

    if(x > curveP[r-1] && x <= curveP[r])
    {
      newCentroidPos = r;
      break;
    }
  }

  centroids.push_back(allCurvesCP[newCentroidPos]);
  //allCurvesCP.push_back(centroids[0]);
  allCurvesCP.erase(allCurvesCP.begin()+(newCentroidPos));
  //centroids.erase(centroids.begin());
}


void MainInitializationPP(vector<vector<vector<long double>>>& allCurvesCP, vector<vector<vector<long double>>>& centroids, vector<FrechetValues>& Fds){

  long double minDistance;
  long double Elem;
  long double sum = 0.0;

  vector<long double> distanceVec;
  vector<long double> curveP;

  /*gia kathe simeio tou dataset briskoume tin kontinotero apostasi me to kontinotero kentroeides */
  for(unsigned j = 0 ; j < allCurvesCP.size() - centroids.size(); j++) //gia kathe simeio
  {
    minDistance = std::numeric_limits<long double>::infinity();

    for(unsigned i = 0 ; i < centroids.size() ; i++) //gia kathe ipopsifio kentroeides metrame thn apostash kai an einai mikroterh thn kratame
    {

      Elem = FrechetDistance(allCurvesCP[j], centroids[i]);
      /*Fds.push_back(FrechetValues());
      Fds[j].CurveI = allCurvesCP[j] ;
      Fds[j].CurveJ = centroids[i];
      Fds[j].FrechetDistance = Elem;
      //Elem = rand();*/

      if (minDistance > Elem) minDistance = Elem;

    }

    distanceVec.push_back(minDistance); //gemizei enas pinakas megethous n - t (opou t ta kentroeidh mexri twra) me tis pio kontines tous apostaseis se kentroeides
  }

  for (unsigned i = 0; i < (allCurvesCP.size() - centroids.size()); ++i) //YPOLOGIZOUME TO SUM TOU TYPOU
  {
    	sum+= pow(distanceVec[i], 2);
	}

	//twra h pithanothta na epilexthei to i-osto curve einai minDistance[i]^2 / sum;
	//prepei na epiletxhei to epomeno kentroeides uniformly random me aytes tis pithanothtes
  for (unsigned i = 0; i < (allCurvesCP.size() - centroids.size()); ++i)
  {
  	curveP.push_back(pow(distanceVec[i], 2) / sum); //P.X. H 5h kampylh exei curveP[5]% na dialexthei san neo kentroeides

    if(i > 0) {
      curveP[i]+=curveP[i-1];
    }

	}

  findNewCentroid(allCurvesCP, centroids, curveP);

	//curveP.clear();
	//minDistance.clear();

  /*if (NOOFCENTROIDS == size.centroids()) return;
  else PrepareForFindingCentroid(vector<vector<vector<long double>>>& allCurvesCP, vector<vector<vector<long double>>>& centroids);*/
}


int initializationPlusPlus(vector<vector<vector<long double>>>& all_curves, vector<vector<vector<long double>>>& centroids, vector<FrechetValues>& Fds){

  long double x = selectUniformlyRandom(0, all_curves.size()-1.0);

  int noofCentroids = 0;

  centroids.push_back(all_curves[x]);
  all_curves.erase(all_curves.begin()+x);

  for(; noofCentroids < NOOFCENTROIDS; noofCentroids++){

    MainInitializationPP(all_curves, centroids, Fds);
    if(noofCentroids == 0) {
        centroids.erase(centroids.begin());
    }

  }

  return 0;
}
