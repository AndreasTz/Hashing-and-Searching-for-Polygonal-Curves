#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

#include "Frechet.h"
#include "Team.h"
#include "VectorUtils.h"
#include "Initializationpp.h"
#include "LloydsAssignment.h"
#include "UpdateFuncts.h"
#include "Reading.h"
#include "Hashing.h"
#include "RangeSearch.h"
#include "outputFuncs.h"

int NOOFCENTROIDS;
int dimension;
int NoofCurves;

using namespace std;
using namespace Utils;

string menuSelectTypeOfInitialization();
string menuSelectTypeOfAssignment();
string menuSelectTypeOfUpdate();
string checkForContinue();



int main(int argc, char* argv[]){

  string answerForContinue;
  string TypeOfUpdate;
  string TypeOfAssignment;
  string TypeOfInit;

  PreferedDetails details;
  readingFromCMD(argc, argv, details);

  Parameters parameters;
  readingConfFile(details.configurationFile, parameters);
  NOOFCENTROIDS = parameters.number_of_clusters;

  ifstream myfile;
  OpenFile(myfile, details.inputFile);

  dimension = EstimateDimensions(myfile);

  NoofCurves = EstimateTotalLines(myfile);

  vector<vector<vector<long double>>> AllCurves (NoofCurves, vector<vector<long double> >(dimension));
  vector<vector<vector<long double>>> AllCurvesCP (NoofCurves, vector<vector<long double> >(dimension));

  HashMap ** HashArray;

  HashArray = new HashMap* [parameters.number_of_hash_tables];

  for(int i = 0; i < parameters.number_of_hash_tables ; i++){
    HashArray[i] = new HashMap();
  }

  int answer;

  do{
    cout << "Please enter the type of Hashing : \n 1: For Classic \n 2: For Probabilistic" << endl;
    cin >> answer;
  }while(answer != 1 && answer != 2);

  vector<string> nameVector;

  readingFromFile(myfile, AllCurves, parameters.number_of_hash_tables, parameters.number_of_grid_curves, HashArray, answer , nameVector);

  AllCurvesCP = AllCurves;

  myfile.close();

  vector<long double> Silhouette;
  vector<vector<vector<long double>>> centroids;//(NOOFCENTROIDS, vector<vector<long double> >(1,vector< long double> (dimension)));
  //vector<vector<vector<long double>>> centroids (NOOFCENTROIDS, vector<vector<long double> >(dimension));
  vector<vector<vector<long double>>> secondMinCentroids;
  vector<FrechetValues> Fds;
  int updated;
  double elapsed_secsI , elapsed_secsAU;// , elapsed_secsU;
  double totalTime;

  Team * TeamArray = new Team[parameters.number_of_clusters];
  for(unsigned i =0 ; i < (unsigned)parameters.number_of_clusters ; i++ ){
    Team T (i);
    TeamArray[i]= T;
  }

  Team * secBestTeamArray = new Team[parameters.number_of_clusters];
  for(unsigned i =0 ; i < (unsigned)parameters.number_of_clusters ; i++ ){
    Team T (i);
    secBestTeamArray[i]= T;
  }


  do{

    TypeOfInit = menuSelectTypeOfInitialization();
    TypeOfAssignment = menuSelectTypeOfAssignment();
    TypeOfUpdate = menuSelectTypeOfUpdate();

    clock_t begin = clock();

    centroids.clear();
    if(TypeOfInit == "Init++"){

      initializationPlusPlus(AllCurves, centroids, Fds);

    }
    else if(TypeOfInit == "Simple"){

      simplestInitialization(AllCurves, centroids); // den ginetai klisi tis frechet

    }
    secondMinCentroids = centroids;

    clock_t end = clock();
    elapsed_secsI = double(end - begin) / CLOCKS_PER_SEC;

    cout << " END OF INIT: " << elapsed_secsI << endl;


    begin = clock();
    do{
      if(TypeOfAssignment == "Lloyd's"){

        SimplestAssignment(AllCurves, centroids, secondMinCentroids, TeamArray, secBestTeamArray, Fds);

      }
      else if(TypeOfAssignment == "RangeSearch"){

        RangeSearch(centroids, secondMinCentroids, AllCurves, TeamArray, secBestTeamArray,
          parameters.number_of_grid_curves, parameters.number_of_hash_tables, answer,
          details.metric, HashArray, Fds);

      }

      cout << "END OF ASSIGNMENT" << endl;
      if(TypeOfUpdate == "Frechet"){
        if(!details.metric.compare("DTW")){
            cout << "THIS CAN'T BE DONE" << endl;
            updated = 0;
            break;
        }
        updated = FindOptimalCentroidFDFDN(parameters.number_of_clusters, AllCurves, centroids, secondMinCentroids, TeamArray);
        updated = 0;
      }
      else if(TypeOfUpdate == "PAM"){

        updated = PAM_algorithm(AllCurves, centroids, secondMinCentroids, TeamArray, secBestTeamArray, Fds);
        updated = 0;
      }
      cout << "END OF UPDATE" << endl;
    }while(updated);

    cout << "END OF LOOP" << endl;
    end = clock();
    elapsed_secsAU = double(end - begin) / CLOCKS_PER_SEC;
    totalTime = elapsed_secsAU + elapsed_secsI;

    EstimateSilhouette(parameters.number_of_clusters, centroids, AllCurves, Silhouette, TeamArray, secBestTeamArray, secondMinCentroids);
    cout << "END OF Silhouette"<< endl;
	  PrintResults(details.outputFile, AllCurves, parameters.number_of_clusters, TypeOfAssignment, TypeOfInit, TypeOfUpdate, details.metric, TeamArray, details.CompleteParamIShere, totalTime, Silhouette, nameVector);

	  AllCurves = AllCurvesCP;

    answerForContinue = checkForContinue();

  }while(!answerForContinue.compare("yes"));

  delete [] TeamArray;
  delete [] secBestTeamArray;


  for(int i = 0; i < parameters.number_of_hash_tables ; i++){
	   delete HashArray[i];
  }
  delete [] HashArray;

  return 0;
}


string menuSelectTypeOfInitialization()
{
  string answer;
  string TypeOfInit;
  do{
    cout << " Select the type of initialization: " << endl << " 1: for initialization++ \n 2: for simple initialization " << endl;
    cin >> answer;
    if(answer == "1"){

      TypeOfInit = "Init++";
    }
    else if(answer == "2"){

      TypeOfInit ="Simple";
    }

  } while(answer.compare("1") && answer.compare("2"));
  return(TypeOfInit);
}


string menuSelectTypeOfAssignment()
{
  string answer;
  string TypeOfAssignment;
  do{
    cout << " Select the type of Assignment: " << endl << " 1: for Lloyd’s assignment (simplest approach) \n 2: for Assignment by Range search (LSH)" << endl;
    cin >> answer;
    if(answer == "1"){
      TypeOfAssignment = "Lloyd's";
    }
    else if(answer == "2"){
      TypeOfAssignment = "RangeSearch";
    }

  } while(answer.compare("1") && answer.compare("2"));
  return (TypeOfAssignment);
}


string menuSelectTypeOfUpdate()
{
  string answer;
  string TypeOfUpdate;
  do{
    cout << " Select the type of Assignment: " << endl << " 1: for Mean Discrete Frechet curve \n 2: for Partitioning Around Medoids (PAM) – Improved update" << endl;
    cin >> answer;
    if(answer == "1"){
      TypeOfUpdate = "Frechet";
    }
    else if(answer == "2"){
      TypeOfUpdate = "PAM";
    }

  } while(answer.compare("1") && answer.compare("2"));

  return (TypeOfUpdate);
}


string checkForContinue()
{
  string answerForContinue;

  cout << "Wanna continue? (yes/no)" << endl;
  cin >> answerForContinue;
  while(answerForContinue.compare("yes") && answerForContinue.compare("no")){
    cout << "Please type yes/no" << endl;
    cin >> answerForContinue;
  }
  return answerForContinue;
}
