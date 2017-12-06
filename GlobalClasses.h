#ifndef GLOBALCLASSES__H
#define GLOBALCLASSES__H
#include <vector>
#include <iostream>
#include <cstring>

#include "VectorUtils.h"

using namespace std;

class Curve{
public:
			int curvePlace;
	    string curve_id;
	    int noofPointsInCurve;
	    vector<vector<long double> > curvePoints;

      void printCurveDetails(){
        cout << "Curve id: " << this->curve_id << endl;
        cout << "noofPointsInCurve: " << this->noofPointsInCurve << endl;
        cout << "Curve Points: " << endl;
        Utils::printVectorOfVector(curvePoints);
      }
};


class PreferedDetails{

	public:
		string inputFile;
		string configurationFile;
		string outputFile;
    string metric;
		int CompleteParamIShere;

    void setInputFile(string ifile){
      this->inputFile  = ifile;
    }
    string getInputFile(){
      return this->inputFile;
    }
    void setOutputFile(string ofile){
      this->outputFile  = ofile;
    }
    string getOutputFile(){
      return this->outputFile;
    }
    void setConfigurationFile(string cfile){
      this->configurationFile = cfile;
    }
    string getConfigurationFile(){
      return this->configurationFile;
    }
    void setMetric(string metric){
      this->  metric= metric;
    }
    string getMetric(){
      return this->metric;
    }
    void printPreferedDetails(){
      cout << "Input File: "<< this->inputFile <<endl;
      cout << "Output File: " << this->outputFile << endl;
      cout << "Configuration File: " << this->configurationFile << endl;
      cout << "Metric: " << this->metric << endl;
    }
};


class Parameters{
public:
  int number_of_clusters;
  int number_of_grid_curves; //default:2
  int number_of_hash_tables;

  Parameters(){
    this->number_of_grid_curves = 2;
    this->number_of_hash_tables = 3;
  }
  void setNoofClusters(int parameter){this-> number_of_clusters = parameter ;}
  void setNoofGridCurves(int parameter){this-> number_of_grid_curves = parameter;}
  void setNoofHT(int parameter){this-> number_of_hash_tables = parameter;}
  int getNoofClusters(){return this->number_of_clusters;}
  int getNoofGridCurves(){return this->number_of_grid_curves;}
  int getNoofHT(){return this->number_of_hash_tables;}
  void PrintParameters(){
    cout << "Number of HTs " << this->number_of_hash_tables << endl;
    cout << "Number of Grid Curves " << this->number_of_grid_curves << endl;
    cout << "number_of_clusters " << this->number_of_clusters << endl;
  }
};


class FrechetValues{
public:
	vector<vector<long double> >  CurveI;
	vector<vector<long double> >  CurveJ;
	long double FrechetDistance;

};
#endif
