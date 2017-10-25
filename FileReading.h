#ifndef FILEREADING__H
#define FILEREADING__H

#include "Hashing.h"
#include "HelpClasses.h"

extern double R;
extern double dimension;

class InitialCurve{
  public:

	    string curve_id;
	    int noofPointsInCurve;
	    double ** curvePoints;

	    InitialCurve(){

        this -> curvePoints = new double*[this -> noofPointsInCurve];
        for(int i = 0; i < this -> noofPointsInCurve; i++){
            this -> curvePoints[i] = new double[(int)dimension];
          }
      }
};


HashEntry* readingFromFile(string Filename , HashMap ** const HashArray,PreferedDetails * const details, vector<vector<double>>* v);



#endif
