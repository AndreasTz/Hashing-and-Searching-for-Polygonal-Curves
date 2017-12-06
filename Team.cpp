#include "VectorUtils.h"
#include <iostream>

#include "Team.h"

using namespace std;
using namespace Utils;

Team::Team(){
  cout << "Constructor" << endl;
}

Team::Team(int teamID){
  this->TeamID = teamID;
}

void Team::SetCentroidID(int centroidId){
  this->CentroidID = centroidId;
}

void Team::SetCentroid(vector<vector<long double>>& centroid){
  this->Centroid = centroid;
}

void Team::InsertMember(vector<vector<long double>>& Newmember){
    this->members.push_back(Newmember);
}

void Team::PrintDetails(){
  cout << " Team: " << this->TeamID << endl;
  cout << " Current Centroid ID: " << this->CentroidID << endl;
  cout << "CENTROID'S COORDS: "<<endl;
  printVectorOfVector(this->Centroid);
  cout << " Members are points: " << endl;
  printVectorOfVectorOfVector(this->members);
}
