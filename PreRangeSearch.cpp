#include <iostream>
#include <cmath>
#include "PreRangeSearch.h"
using namespace std;

#define DELTA 0.1
#define K_VEC 3

extern int dimension;

vector<int> rVector;

void addtoR(vector<int>& v, int d)
{
  while (d)
  {
    v.push_back((rand() % 101));
    d--;
  }
}


void removeDuplicates(vector<vector<long double>>& curvePoints, int dimension, int& noofPointsInCurve)
{
  int flag = 0;
  int count = 1;
  int found = 0;
  int thesi = count -found;

  for(unsigned i = 1; i < curvePoints.size(); i++) //tha ginei gia kathe stoixeio tis curve
  {
    if(curvePoints[thesi - 1][0] != curvePoints[thesi][0] ){
      flag = 0;

    }
    else{
      flag++ ;

      for(int j = 1 ; j < dimension ; j++){
        if(curvePoints[thesi-1][j] == curvePoints[thesi][j] ){
          flag++;
        }
      }

      if(flag == dimension){

        noofPointsInCurve--;
        found++;

        curvePoints.erase(curvePoints.begin()+ thesi);

      }

    }
    count++;
    thesi = count - found;
    flag = 0;

  }
//  Utils::printVectorOfVector(curvePoints);
}


int FindHashValue(const vector<long double>& concVector)
{
  if (rVector.size() < concVector.size())
  {
    addtoR(rVector, (concVector.size() - rVector.size()));
  }
  int sumKey = 0;
  for (unsigned i = 0; i < concVector.size(); i++)
  {
    sumKey += (concVector[i] * rVector[i]);
  }
  return sumKey;
}


/*synartisi i opoia upologizei to eswteriko ginomeno duo dianismatwn
Exei ginei mia mikri parallagi vevaia gia tin periptwsi pou ta dianismata den exoun to idio megethos
Eisagoume ston vector vec2 (alliws v tou projection) epipleon stoixeia mono an |vec1| > |vec2|
Giati theoroume oti to v prepei na simvadizei me to megalitero dianisma
*/
long double multiplyVectors(vector<vector<long double> >& vec1, vector<vector<long double> >& vec2){
  double result = 0.0;

  //cout << "vec1.size() > vec2.size()" << vec1.size() << " "<< vec2.size() << endl;
  vector<long double> point;
  if(vec1.size() > vec2.size()){ //Prepei na auksisoyme to megethos tou vector v
    unsigned int diff = vec1.size() - vec2.size();
    for(unsigned i = 0 ; i < diff; ++i){

      point.clear();
      for(unsigned j = 0 ; j < vec1[i].size(); j++){
        point.push_back(selectFromNormalDistr());
      }
      vec2.push_back(point);

    }

  }

  //Exoume 2 theoritika isomegethi dianusmata
  for(unsigned i = 0 ; i < vec1.size() ; ++i){

    for(unsigned j = 0 ; j < vec1[i].size(); j++){
        result = result + (vec1[i][j]* vec2[i][j]);

    }

  }

  return result;
}


/*
Sunartisi i opoia epistrefei enan arithmo apo kanoniki katanomi me vasi tin methodo Marsaglia twn diafaneiwn
*/
long double selectFromNormalDistr() {

  static int count = 0;
  static double nextGaussianVal;
  double firstGaussianVal, val1, val2, s;

 if (count == 0) {
    do {
        val1 = 2 * ((double) rand() / (RAND_MAX)) - 1;  // between -1.0 and 1.0
        val2 = 2 * ((double) rand() / (RAND_MAX)) - 1;  // between -1.0 and 1.0
        s = val1 * val1 + val2 * val2;
     } while (s >= 1 || s == 0);
     double multiplier = sqrt(-2 * log(s)/s);
     nextGaussianVal = val2 * multiplier;
     firstGaussianVal = val1 * multiplier;
     count = 1;
     return firstGaussianVal;
 }

 count = 0;
 return abs(nextGaussianVal);
}


/*
Synartisi i opoia ypologizei to euklideio hash
me basi twn tipo h= floor((point * v + t) /w)
  input :
          all_K_gridCurvesVecNoDublicates (to concat twn k grid-curve)
          singleHashFuncVec (to apotelesma)
  output : -
*/
void createVecFunc(vector<vector<long double>>& KConcVec, vector<long double>& singleHashFuncVec){

  const int w = 4;
  long double shiftFactor;
  long double multRes;
  long double sum;
  long double divRes;
  int total;

  vector<vector<long double>> v; /* O vector v einai o antistoixos vector tis eksiswsis kai einai global epeidi den thelw na kratiountai ta stoixeia tou gia kathe fora pou mpainei*/

  shiftFactor = selectUniformlyRandom(w);

  multRes= multiplyVectors(KConcVec, v);

  sum = multRes + shiftFactor;
  divRes = sum / w;
  total =   floor(divRes);
  singleHashFuncVec.push_back(total);

}



int ProbabilisticFindHashValue(vector<vector<long double>>& concVector)
{
  vector<long double> concatKVecHashFunc; //vector pou periexei tis kvec hashFunctions
  vector<long double> singleHashFuncVec; //vector pou periexei 1 hashFunction kathe fora
  long double elem;
  int sizeOfVec;
  /*evresi euklideias LSH sunartisis*/
  for(int i = 0 ; i < K_VEC ; i++){
    singleHashFuncVec.clear();

    createVecFunc(concVector, singleHashFuncVec);
    sizeOfVec = singleHashFuncVec.size();
    for(int i = 0 ; i < sizeOfVec; i++){
      elem = singleHashFuncVec.back();
      singleHashFuncVec.pop_back();
      concatKVecHashFunc.push_back(elem);
    }
  }
  int hashKey = FindHashValue(concatKVecHashFunc);

  return hashKey;
}


long double selectUniformlyRandom(long double maxValue){

  double min = 0.0;
  double max = maxValue ;
  return min + (double) ((max-min+1.0) * (rand() / (RAND_MAX + 1.0)));
}


void selectDisplacedFactor(vector<long double>& t, long double lenOfVec){
  t.push_back(selectUniformlyRandom(lenOfVec));

  int newt;
  for(int i = 1; i < (int)lenOfVec; i++){ //gia kathe diastasi

    newt = selectUniformlyRandom(lenOfVec);
    t.push_back(newt);

  }
}


void makeKgridCurves(int noofGridCurves, vector<vector<long double>>& Curve, vector<long double>& concatVec)
{
  int roundedRes;
  int noofPointsInCurve;
  long double diff;
  long double res;
  long double gridPoint;
  vector <long double> displacedFactorVec;
  //cout << " Curve size: " << Curve[0].size() << endl; curve.size[0] ==dimension
  for(int k = 0 ; k  < noofGridCurves ; k++ )
  {
      vector<vector<long double>> dispGridCurve;

      displacedFactorVec.clear();
      selectDisplacedFactor(displacedFactorVec, Curve[0].size());
      //cout << "DISP F:" ;
      //Utils::printVector(displacedFactorVec);

      //cout << "Curve with points:" <<endl;
      //Utils::printVectorOfVector(Curve);

      for(unsigned i = 0 ; i < Curve.size() ; i++) //gia kathe simeio tis kampilis
      {
        vector<long double> dispGridPoint;
        for(unsigned j = 0 ; j < Curve[i].size(); j++) //gia kathe diastasi
        {
          diff = Curve[i][j] - displacedFactorVec[j];
          if(diff < 0)
            diff = -diff*(1.0);
          res = diff / DELTA;

          roundedRes = round(res);

          gridPoint = roundedRes* DELTA;

          dispGridPoint.push_back(gridPoint);
        }

        dispGridCurve.push_back(dispGridPoint);
        noofPointsInCurve = dispGridCurve.size();
        removeDuplicates(dispGridCurve,(int) dispGridPoint.size(),noofPointsInCurve);
      }

      //cout << "dispGridCurve:" << endl;
      //Utils::printVectorOfVector(dispGridCurve);

      for(unsigned i = 0 ; i < dispGridCurve.size() ; i++)
      {
        for(unsigned j = 0 ; j < Curve[i].size(); j++)
        {
          concatVec.push_back(dispGridCurve[i][j]);
        }
      }
  }

}


void PreRangeSearch(Curve& curve, int noofHTs, int noofGridCurves, HashMap** HTArray, int type) //isws xreiastei kai san orisma o arithmos twn grammwn tou arxeiou
{

  int hashKey;

  vector<long double> concatVec;

  for(int i = 0; i < noofHTs ; i++ )
  {

    makeKgridCurves(noofGridCurves, curve.curvePoints, concatVec);

    //cout << "concatVec::: " << endl;
    //Utils::printVector(concatVec);
    if(type == 1){
      hashKey = FindHashValue(concatVec);
    }
    else{
      hashKey = ProbabilisticFindHashValue(curve.curvePoints);
    }
    Element Elem ;
    Elem.ID = curve.curvePlace;
    Elem.mName = curve.curve_id;
    Elem.gC = concatVec;
    Elem.assigned = 0;
    HTArray[i]->put(hashKey, Elem);
  }

}
