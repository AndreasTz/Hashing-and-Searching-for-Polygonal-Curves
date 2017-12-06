#ifndef VECTORUTILS__H
#define VECTORUTILS__H

#include <vector>
#include <iostream>

using namespace std;

namespace Utils{

  long double findMinElemFromVector(vector<long double>& distanceVec);

  long double findMaxElemFromVector(vector<long double>& distanceVec);

  template<typename TypeX>
  void printVector(const vector<TypeX>& t){

    for (double i : t)
      cout << i << ' ';

    cout << endl;
  }


  template<typename TypeX>
  void printVectorOfVector(const vector<vector<TypeX> >& vecVec){

    for(unsigned i = 0 ; i < vecVec.size(); i++){
      printVector(vecVec[i]);
      cout << endl;
    }

  }


  template<typename TypeX>
  void printVectorOfVectorOfVector(const vector<vector<TypeX> >& vecVecVec){

    for(unsigned i = 0 ; i < vecVecVec.size(); i++){
      printVectorOfVector(vecVecVec[i]);
      cout << endl;
    }

  }

  template <class T>
  static bool compareVectors(vector<T>& a, const vector<T> & b)
  {

      if (a.size() != b.size()) return false;

      sort(a.begin(), a.end());
      for (const auto & v : b)
          if ( !binary_search(a.begin(), a.end(), v) ) return false;
      return true;
  }

  template <typename T>
  int findElemInVec(const vector<long double>& toFind, vector<T>& HA)
  {
  	for(int i = 0 ; i < HA.size(); i++)
  	{
  		if(HA[i].Elem == toFind){
  			return i;
  		}
  	}
  	return -1;
  }

  template <typename T>
  int findElemInVec2(vector<vector<long double> > & toFind,vector<vector<long double> > & toFind2, vector<T>& HA)
  {

  	for(int i = 0 ; i < HA.size(); i++)
  	{
  		if((compareVectors(HA[i].CurveI,toFind) && compareVectors(HA[i].CurveJ,toFind2)) || (compareVectors(HA[i].CurveI , toFind2) && compareVectors(HA[i].CurveJ , toFind))){
  			return i;
  		}
  	}
  	return -1;
  }

}



#endif
