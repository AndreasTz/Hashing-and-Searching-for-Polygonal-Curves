#ifndef TEAM__H
#define TEAM__H

#include <vector>


using namespace std;

class Team {
public:
    int TeamID;
    int CentroidID;
    vector<vector<long double> > Centroid;
    vector<vector<vector<long double> > > members;
    Team();

    Team(int teamID);

    void SetCentroidID(int centroidId);

    void SetCentroid(vector< vector<long double> >& centroid);

    void InsertMember(vector< vector <long double> >& Newmember);

    void PrintDetails();

};


#endif
