#include <iostream>
#include <limits>
#include <algorithm>
#include <map>


#include "PreRangeSearch.h"
#include "VectorUtils.h"
#include "Frechet.h"
#include "RangeSearch.h"
#include "Team.h"

using namespace std;
 extern int NOOFCENTROIDS;
 extern int dimension;


long double findInitialRange(vector<vector<vector<long double>>>& centroids, vector<FrechetValues>& Fds)
{
  //vector<long double> centroidsDistance;
  long double distance;
  long double minDist;
  long double Range;
  //int th;
  minDist = std::numeric_limits<long double>::infinity();
  for(unsigned i = 1; i < centroids.size() ; i++) //gia kathe kentroeides
  {
    distance = FrechetDistance(centroids[i], centroids[i-1]);
  /*  if((th = Utils::findElemInVec2(centroids[i], centroids[i-1], Fds))>0){
      distance = Fds[th].FrechetDistance;
    }
    else{
      distance = FrechetDistance(centroids[i], centroids[i-1]);
      Fds.push_back(FrechetValues());
      Fds[Fds.size()-1].CurveI = centroids[i];
      Fds[Fds.size()-1].CurveJ = centroids[i-1];
      Fds[Fds.size()-1].FrechetDistance = distance;
    }*/
    //centroidsDistance.push_back(distance);
    if(distance < minDist)
    {
      minDist = distance;
    }

  }

  // minDist = Utils::findMinElemFromVector(centroidsDistance);
  Range = minDist / 2;

  return (Range);
}




struct HelpRAAsignment{
public:
  vector <long double> Elem;
  int ElemID;
  int centroidID;
  vector<vector<long double> > centroidToBe;
  int assigned;
};



void RangeSearch(vector<vector<vector<long double>>>& centroids, vector<vector<vector<long double>>>& secBestCentroids, vector<vector<vector<long double>>>& AllCurves,
  Team * TeamArray, Team* secBestTeamArray, int noofGridCurves, int noofHTs, int type, string metric,
  HashMap** HashArray, vector<FrechetValues>& Fds)
  {

  vector<long double> concatVec;
  vector<long double> secConcatVec;
  int hashKey;
  int secHashKey;
  int count = 0;

  struct HelpRAAsignment HA;
  vector<HelpRAAsignment> vecAsign;
  vector<HelpRAAsignment> vecAsign2;

  long double Range = findInitialRange(centroids, Fds);
  int th, th2;

  for(unsigned k = 0 ; k < AllCurves.size(); k++){ //Gia KATHE STOIXEIO

    vecAsign.push_back(HelpRAAsignment());
    vecAsign[k].assigned =0;

    vecAsign2.push_back(HelpRAAsignment());
    vecAsign2[k].assigned =0;

  }

  for(unsigned j = 0 ; j < centroids.size(); j++){
      TeamArray[j].members.clear();
      TeamArray[j].SetCentroidID(j);
      TeamArray[j].Centroid = centroids[j];
  }

  for(unsigned j = 0 ; j < secBestCentroids.size(); j++){
      secBestTeamArray[j].members.clear();
      secBestTeamArray[j].SetCentroidID(j);
      secBestTeamArray[j].Centroid = secBestCentroids[j];
  }
  int thesi1 =0 ;
  int thesi2 = 0 ;
  do{
    //count = 0;
    for(unsigned i = 0; i < centroids.size() ; i++) //gia kathe kentroeides
    {
      //count = 0;
      for(int j=0 ;j < noofHTs ;j++ ){ //gia L Hash Tables

        makeKgridCurves(noofGridCurves , centroids[i] , concatVec); //bres poio einai to "fingerPrint" tou
        makeKgridCurves(noofGridCurves, secBestCentroids[i], secConcatVec);
        //briskoume se poio bucket anikei
        if(type == 1){ //an thelei klassiko hashing
          hashKey = FindHashValue(concatVec);
          secHashKey = FindHashValue(secConcatVec);
        }
        else{ //an thelei Probabilistic hashing
         hashKey = ProbabilisticFindHashValue(centroids[i]);
         secHashKey = ProbabilisticFindHashValue(secBestCentroids[i]);
        }

        //Pare to bucket pou thes
        for (auto& x : HashArray[j]->getBucket(hashKey))
        {

          if  (Utils::compareVectors(concatVec , x.gC) == false)
          { //an einai idio apla min to upologizeis - upologise ola ta upoloipa

            long double TrueDistance;

            if (!metric.compare("DTW")) TrueDistance = DTWDistanceFromID(concatVec, x.gC);

            else TrueDistance = FrechetDistanceFromID(concatVec, x.gC, dimension);

            if(TrueDistance < Range){

              th = Utils::findElemInVec(x.gC, vecAsign);

              if( th == -1) //an den exei anatethei pouthena
              {
                vecAsign.push_back(HelpRAAsignment());
                vecAsign[thesi1].Elem =x.gC;
                vecAsign[thesi1].ElemID = x.ID;
                vecAsign[thesi1].assigned = 1;
                vecAsign[thesi1].centroidToBe = centroids[i];
                vecAsign[thesi1].centroidID = i;

                thesi1++;
              }
              else //if(vecAsign[th].assigned == 1) //an yparxei sti lista twn ipopsifiwn kentroidwn
              {
                  //Sugkrine tin Frechet twn upopsifiwn kentroeidwn
                  long double Dist1= FrechetDistance(vecAsign[th].centroidToBe, AllCurves[x.ID]);

                  /*if((th2 = Utils::findElemInVec2(vecAsign[th].centroidToBe, AllCurves[x.ID], Fds))> 0){
                    Dist1 = Fds[th2].FrechetDistance;
                  }
                  else{
                    Dist1= FrechetDistance(vecAsign[th].centroidToBe, AllCurves[x.ID]); //synekrine to teleytaio pou tou anatethike
                    Fds.push_back(FrechetValues());
                    Fds[Fds.size()-1].CurveI = vecAsign[th].centroidToBe;
                    Fds[Fds.size()-1].CurveJ = AllCurves[x.ID];
                    Fds[Fds.size()-1].FrechetDistance = Dist1;

                  }*/

                  long double Dist2 = FrechetDistance(centroids[i], AllCurves[x.ID]);

                  /*if((th2 = Utils::findElemInVec2(centroids[i], AllCurves[x.ID], Fds))>0){
                    Dist2 = Fds[th2].FrechetDistance;
                  }
                  else{
                    Dist2 = FrechetDistance(centroids[i], AllCurves[x.ID]);  //me to paron kentroides
                    Fds.push_back(FrechetValues());
                    Fds[Fds.size()-1].CurveI = centroids[i];
                    Fds[Fds.size()-1].CurveJ = AllCurves[x.ID];
                    Fds[Fds.size()-1].FrechetDistance = Dist2;
                  }*/
                  if(Dist2 < Dist1){
                    vecAsign[th].centroidToBe = centroids[i];
                    vecAsign[th].centroidID = i;
                  }
              }
            }
          }
        }

        //////////////////////////////////////////////////////////////////////
        count = 0;
        for (auto& x : HashArray[j]->getBucket(secHashKey))
        {
          if  (Utils::compareVectors(secConcatVec , x.gC) == false)
          { //an einai idio apla min to upologizeis - upologise ola ta upoloipa

            long double TrueDistance;

            if (!metric.compare("DTW")) TrueDistance = DTWDistanceFromID(secConcatVec, x.gC);

            else TrueDistance = FrechetDistanceFromID(secConcatVec, x.gC, dimension);

            if(TrueDistance < Range){

              th = Utils::findElemInVec(x.gC, vecAsign2);

              if( th == -1) //an den exei anatethei pouthena
              {
                vecAsign2.push_back(HelpRAAsignment());
                vecAsign2[thesi2].Elem =x.gC;
                vecAsign2[thesi2].ElemID = x.ID;
                vecAsign2[thesi2].assigned = 1;
                vecAsign2[thesi2].centroidToBe = secBestCentroids[i];
                vecAsign2[thesi2].centroidID = i;

                thesi2++;
              }
              else //if(vecAsign2[th].assigned == 1) //an yparxei sti lista twn ipopsifiwn kentroidwn
              {
                  //Sugkrine tin Frechet twn upopsifiwn kentroeidwn
                  long double Dist1 = FrechetDistance(vecAsign2[th].centroidToBe, AllCurves[x.ID]);

                /*  if((th2 = Utils::findElemInVec2(vecAsign[th].centroidToBe, AllCurves[x.ID], Fds))>0){
                    Dist1 = Fds[th2].FrechetDistance;
                  }
                  else{
                    Dist1= FrechetDistance(vecAsign[th].centroidToBe, AllCurves[x.ID]); //synekrine to teleytaio pou tou anatethike
                    Fds.push_back(FrechetValues());
                    Fds[Fds.size()-1].CurveI = vecAsign[th].centroidToBe;
                    Fds[Fds.size()-1].CurveJ = AllCurves[x.ID];
                    Fds[Fds.size()-1].FrechetDistance = Dist1;

                  }*/


                  long double Dist2 = FrechetDistance(secBestCentroids[i], AllCurves[x.ID]);

                /*  if((th2 = Utils::findElemInVec2(secBestCentroids[i], AllCurves[x.ID], Fds))>0){
                    Dist2 = Fds[th2].FrechetDistance;
                  }
                  else{
                    Dist2= FrechetDistance(secBestCentroids[i], AllCurves[x.ID]); //synekrine to teleytaio pou tou anatethike
                    Fds.push_back(FrechetValues());
                    Fds[Fds.size()-1].CurveI = secBestCentroids[i];
                    Fds[Fds.size()-1].CurveJ = AllCurves[x.ID];
                    Fds[Fds.size()-1].FrechetDistance = Dist2;

                  }*/


                  if(Dist2 < Dist1){
                    vecAsign2[th].centroidToBe = secBestCentroids[i];
                    vecAsign2[th].centroidID = i;
                  }
              }
            }
          }
        }
      }
      Range*=2;
    }

  }while(Range < pow(10,10));


  long double Dist;
  long double minDist;
  int centroidPos = 0;
//  cout << vecAsign.size() << endl;
  for(unsigned i=0;  i < vecAsign.size(); i++)
  {

    if(vecAsign[i].assigned == 1){
    //  TeamArray[vecAsign[i].centroidID].InsertMember(AllCurves[vecAsign[i].ElemID]);
  //  cout << vecAsign[i].centroidID << endl;
      TeamArray[vecAsign[i].centroidID].members.push_back(AllCurves[vecAsign[i].ElemID]);
    }
    if(vecAsign2[i].assigned == 1){
    //  secBestTeamArray[vecAsign2[i].centroidID].InsertMember(AllCurves[vecAsign2[i].ElemID]);
      secBestTeamArray[vecAsign2[i].centroidID].members.push_back(AllCurves[vecAsign2[i].ElemID]);
    }

  }

  int secBestPos = 0;

  for(unsigned i = 0; i < AllCurves.size(); i++)
  {
    if(vecAsign[i].assigned == 0){
      minDist = std::numeric_limits<long double>::infinity();
      for(unsigned j = 0; j < centroids.size(); j++)
      {

        Dist = FrechetDistance(centroids[j], AllCurves[i]);

        /*if((th2 = Utils::findElemInVec2(centroids[j], AllCurves[i], Fds))>0){
          Dist = Fds[th2].FrechetDistance;
        }
        else{
          Dist = FrechetDistance(centroids[j], AllCurves[i]);
          Fds.push_back(FrechetValues());
          Fds[Fds.size()-1].CurveI = centroids[j];
          Fds[Fds.size()-1].CurveJ = AllCurves[i];
          Fds[Fds.size()-1].FrechetDistance = Dist;
        }*/

        if(minDist > Dist)
        {
          minDist = Dist;
          secBestPos = centroidPos;
          centroidPos = j;
        }

      }

      //TeamArray[centroidPos].InsertMember(AllCurves[i]);
      TeamArray[centroidPos].members.push_back(AllCurves[i]);
      //secBestTeamArray[secBestPos].InsertMember(AllCurves[i]);
      secBestTeamArray[secBestPos].members.push_back(AllCurves[i]);
    }
  }


}
