#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#include "Hashing.h"
#include "HelpClasses.h"
#include "Grid.h"


#define delta 1
#define K_VEC 3

using namespace std;

vector<int> rVector;

//INPUT 2 vector<double>
//OUTPUT: 1 if they are equal, 0 otherwise!


int CompareVectors(vector<double>* v1, vector<double>* v2)
{
  if (v1->size() != v2->size()) return 0;
  for (int i; i<v1->size(); i++)
  {
    if (v1[0][i] != v2[0][i]) return 0;
  }
  return 1;
}

//pretified for element data struct
int CompareHashElementVectors(Element* ele1, Element* ele2)
{
  return CompareVectors(ele1->gridCurve, ele2->gridCurve);
}

//adding size to Rvector when needed
void addtoR(vector<int>* v, int d)
{
  while (d)
  {
    v->push_back((rand() % 101));
    cout << "RANDOM EINAI:: " << v->back() << endl;
    d--;
  }
}

//idk
void deleteR(vector<int>* v)
{
  v->clear();
}

//INPUT v<d>*
//OUTPUT int type hashValue (which will be changed to index in Hashing.cpp functions)
int FindHashValue(vector<double>* concVector)
{
  if (rVector.size() < concVector->size())
  {
    addtoR(&rVector, (concVector->size() - rVector.size()));
  }
  int sumKey = 0;
  for (int i = 0; i < concVector->size(); i++)
  {
    sumKey += (concVector->back() * rVector[i]);
    concVector->pop_back();
  }
  return sumKey;
}


/*
Sunartisi i opoia upologizei kai epistrefei enan tyxaio arithmo (me vasi tin omoiomorfi katanomi) gia tin dimiourgia tyxaiwn metatopismenwn grid
  input : dimension (diastasi tis kampilis)
  output : tyxaios arithmos apo tin omoiomorfi katanomi
*/
double selectUniformlyRandomT(double maxValue){

  double min = 0.0;
  double max = maxValue ;
  double j = min + (double) ((max-min+1.0) * (rand() / (RAND_MAX + 1.0)));

  return j;
}


/*
Synartisi i opoia upologizei to "kontinotero simeio"  enos simeiou tis dotheisas kampilis me to antistoixo grid
O upologismos ginetai simeio simeio gia kathe aksona ksexorista.
  input : dimension (H diastasi tis kampilis)
          curvePoint (Simeio se aksona)
          displacedGrid

  output : minElem (To kontinotero simeio tou grid)

*/
double findMinPointInAnyAxis(double dimension, int axis, double curvePoint, double ** displacedGrid){

  double MinDistance = curvePoint - displacedGrid[0][axis];
  double minElement = displacedGrid[0][axis];

  for(int i=1 ; i < (int)dimension ; i++){

    if(abs(curvePoint - displacedGrid[i][axis] ) < MinDistance){
      MinDistance = curvePoint - displacedGrid[i][axis];
      minElement = displacedGrid[i][axis];
    }

  }

  return (minElement);
}


/*
Sunartisi i opoia apallasei apo diplotypes emfaniseis idiwn simeiwn
  input: newCurvePoints (pinakas o diastasewn noofPointsInCurve* dimension kai oysiastika diatirei ola ta stoixeia kapoias apo tis nees grid curves)
        dimension (diastasi arxikis kampilis)
        noofPointsInCurve (plithos simeiwn tis kampilis)
  output: -
*/
void removeDuplicates(vector<double>* vecWithoutDublicates, double **newCurvePoints, double dimension ,int* noofPointsInCurve){

  int flag = 0 ;
  int k =0;
  int count =0; //poses fores vrika dublicate

  for(int i = 1 ; i < *noofPointsInCurve; i++ ){

    int thesi = i - count;

    if(newCurvePoints[thesi - 1][0] == newCurvePoints[thesi][0] ){
      flag++ ;

      for(int j = 1 ; j < ((int)dimension) - 1; j++){
        cout << newCurvePoints[thesi][j] << newCurvePoints[thesi][j+1];

        if(newCurvePoints[thesi-1][j] == newCurvePoints[thesi][j] ){
          flag++;
        }

      }

      if(flag == ((int) dimension) -1){

        cout << " We have a dublicate!  " << endl;
        for(int k = i-count; k < *noofPointsInCurve-1; k++) {
          for(int j = 0; j < dimension; j++) {

             newCurvePoints[k][j] = newCurvePoints[k+1][j];

            }
        }

        count++;
        *noofPointsInCurve--;
      }
    }
      flag = 0;
  }
//cout << "RM DUP: noofPointsInCurve: " << noofPointsInCurve << endl;
//cout << "RM DUP: dimension: " << dimension << endl;
//cout << "RM DUP: count: " << count << endl;

  for(int i = 0 ; i < *noofPointsInCurve -count;i++){
    for(int j = 0 ; j < (int)dimension ; j++){
      vecWithoutDublicates->push_back(newCurvePoints[i][j]);
      cout << newCurvePoints[i][j] << " ";
      }
    }
   // printVector(vecWithoutDublicates);
}


/*
Sunartisi i opoia ektypwnei ta simeia tou ekastwte grid
  input : typeOfGrid (Xrisimopoieitai kyriws gia tin ektypwsi tou eidous tou grid pou epilegoume na ektypwthei)
          noofRows (To plithos twn grammwn tou epilegomenoy pinaka)
          noofCols (To plithos twn stilwn tou epilegomenoy pinaka)
           printableGrid (O pinakas pou theloume na ektypwthei)
  output : -
*/
void  printGrid(string typeOfGrid, int noofRows ,int noofCols ,double ** printableGrid){

    cout <<  typeOfGrid  << endl;
    for(int i=0 ; i < noofRows ;i++){
      for(int j = 0  ; j < noofCols ; j++ ){
        cout << printableGrid[i][j] << " ";
      }
      cout << endl;
    }

}


/* Sunartisi ektipwsis vector*/
void printVector(vector<double>* t){
  cout << "VECTOR: " << endl;
  for (vector<double>::const_iterator i = t->begin(); i != t->end(); ++i)
    cout << (double)*i << ' ';
  cout << " ***" << endl;
}


/*
Synartisi epilogis tyxaiou vector pros metatopisi
*/
void selectT_Vector(vector<double>* t, double lenOfVec){
  t->push_back(selectUniformlyRandomT(lenOfVec));

  int newt;
  for(int i = 1; i < (int)lenOfVec; i++){ //gia kathe diastasi

    newt = selectUniformlyRandomT(lenOfVec);
    t->push_back(newt);

  }
   //printVector(t);
}


/*
Synartisi i opoia vazei ola ta simeia mias grid curve se ena pio geniko vector pou periexei ta simeia kai twn K grid curve pou apaitountai
  input : singleVec (vector me ta simeia tis MIAS grid-curve)
          resultVec (vector pou ginetai concat)
  output : -
*/
void Concatenation(vector<double> *singleVec, vector<double> * resultVec){
  double elem;

  int sizeOfVec = singleVec->size();

  for(int i = 0 ; i < sizeOfVec; i++){
    elem = singleVec->back();
    singleVec->pop_back();
    resultVec -> push_back(elem);
  }
}


/*
Sunartisi i opoia epistrefei enan arithmo apo kanoniki katanomi*/
double selectFromNormalDistr() {
    double u = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double v = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double r = u * u + v * v;
    if (r == 0 || r > 1) return selectFromNormalDistr();
    double c = sqrt(-2 * log(r) / r);
    return abs(u * c);
}


/*
Sunartisi i opoia apo ena vector briskei ena simeio
input : dimension(diastasi simeiou)
        resultVec (vector apothikeysis apotelesmatos)
        all_K_gridCurvesVecNoDublicatesCP (vector pou periexei kai tis k kampiles plegmatos )
output: -
*/
void findPoint(double dimension, vector<double> *resultVec, vector<double> *all_K_gridCurvesVecNoDublicatesCP){
  double Elem;
  resultVec->clear();
  for(int i = 0; i < dimension ; i++){

    Elem = all_K_gridCurvesVecNoDublicatesCP->back();
    all_K_gridCurvesVecNoDublicatesCP->pop_back();
    resultVec->push_back(Elem);
  }
}


/*
Synartisi i opoia ypologizei to euklideio has
me basi twn tipo h= floor((point * v + t) /w)
  input : dimension(diastasi twn simeiwn)
          all_K_gridCurvesVecNoDublicates (to concat twn k grid-curve)
          singleHashFuncVec (to apotelesma)
  output : -
*/
void createVecFunc(double dimension, vector<double>* all_K_gridCurvesVecNoDublicates, vector<double>* singleHashFuncVec){
  vector<double> v;
  vector<double> tempResultVec;

  const int w = 4;
  double swiftFactor;
  double multRes;
  double sum;
  double divRes;
  int total;

  for(int i = 0 ; i < all_K_gridCurvesVecNoDublicates->size(); i++){

    v.clear();

    swiftFactor = selectUniformlyRandomT((double)w);

    for(int i =0; i < dimension ; i++)
      v.push_back(selectFromNormalDistr());

    tempResultVec.clear();
    findPoint(dimension,&tempResultVec, all_K_gridCurvesVecNoDublicates);

    for(int i = 0 ; i < tempResultVec.size(); i++){
      multRes = tempResultVec[i] * v[i];
    }

    sum = multRes + swiftFactor;
    divRes = sum / w;
    total =   floor(divRes);
    singleHashFuncVec->push_back(total);

  }

}


/*
Synartisi i opoia upologizei to mikrotero a_i gia tin dimiourgia tou arxikou Grid
  input : dimension (diastasi simeiwn kampilis)
          displacedFactor (paragontas metatopisis)
          initialCurveNoDublicatesVec (arxiki kampili xwris diplotipa)
  output: minA(to mikrotero a_i)
*/
double findMinA(int dimension, int row ,int col, vector<vector <double> >* displacedFactor, vector<double>* initialCurveNoDublicatesVec){

  double *a = new double [initialCurveNoDublicatesVec->size()];
  double diff = initialCurveNoDublicatesVec[0][row] - displacedFactor[0][row][0];
  if(diff < 0){
    diff = diff * (-1);
  }

  a[0] = diff / delta;

  double minA = a[0];
  for(int i =1 ; i < dimension; i++){
    diff = initialCurveNoDublicatesVec[0][col] - displacedFactor[0][row][i];
    if(diff < 0){
      diff = diff * (-1);
    }
    a[i] = diff / delta;
    if(minA > a[i]){
      minA =  a[i];
    }

  }
  return minA;

}


/*
Sunartisi i opoia "gemizei" to arxiko Grid me basi to veltisto A.
  input: dimension (diastasi simeiwn kampilis)
        numberOfLocalitySensitiveFunctions (oi fores pou tha dimiourgithei o displacedFactor(d- diastasis))
        vectorOfVectors ( o displacedFactor gia oles tis numberOfLocalitySensitiveFunctions(alliws k)-epanalipseis)
        initialCurveNoDublicatesVec (i arxiki kampili xwris diplotipa)
        Grid (to Grid pou gemizoume)
  output: -
*/
void fillGrid(int dimension, int noofPointsInCurve, int numberOfLocalitySensitiveFunctions, vector< vector<double> >* vectorOfVectors ,vector<double>* initialCurveNoDublicatesVec, double** Grid){

  for(int i = 0; i < numberOfLocalitySensitiveFunctions; i++){
    vector<double> rowVec;
    selectT_Vector(&rowVec,dimension);
    vectorOfVectors->push_back(rowVec);
  }

  for(int i=0 ; i < (int)dimension; i++){
    for(int j = 0  ; j < (int)dimension; j++ ){
      Grid[i][j] = (j+1)* findMinA(dimension, i, j, vectorOfVectors , initialCurveNoDublicatesVec );
    }
  }
}


/*
Synartisi i opoia ektelei ti vasiki leitourgia  gia to LSH kai tin eisagwgi sto Hash Table.
  input:  dimension (diastasi kampilis)
          R (aktina)
          curvePoints (shmeia tis kampilis pou diavazontai ena ena kai apothikeuontai)
          hashArray (Pinakas me deiktes se HashTables)
          details (stoixeia voithitikis klasis gia ta arxika stoixeia pou prostithentai)
  output: -
*/
void operation(int curve_id, double dimension, int R, double ** curvePoints , int noofPointsInCurve , HashMap ** const HashArray, PreferedDetails * const details, vector<vector<double>>* v){

  // printGrid("Initial Curve", noofPointsInCurve ,dimension ,curvePoints);
  vector<double> initialCurveNoDublicatesVec;
  removeDuplicates(&initialCurveNoDublicatesVec, curvePoints, dimension, &noofPointsInCurve);
  cout << "noofPointsInCurve: " << noofPointsInCurve <<endl;
  v->push_back(initialCurveNoDublicatesVec);

  double ** Grid = new double* [(int)dimension];
  for(int i = 0; i < (int)dimension; i++){
      Grid[i] = new double[(int)dimension];
  }

  vector< vector<double> > displacedFactorsForKTimes;
  fillGrid(dimension, details->numberOfLocalitySensitiveFunctions, noofPointsInCurve, &displacedFactorsForKTimes, &initialCurveNoDublicatesVec, Grid);
  //printGrid("Grid", dimension, dimension, Grid);

  vector<double> singleVecNoDublicates;
  vector<double> all_K_gridCurvesVecNoDublicates; ///concatenated vector

  for(int l = 0; l < details->numberOfHashingArrays; l++){  //L- fores
    for(int i = 0; i < details->numberOfLocalitySensitiveFunctions; i++){  //k- fores

      double ** displacedGrid = new double* [(int)dimension];

      for(int i = 0; i < (int)dimension; i++){
          displacedGrid[i] = new double[(int)dimension];
      }

      for(int i=0 ; i < (int)dimension ;i++){
        for(int j = 0  ; j < (int)dimension ; j++ ){
          displacedGrid[i][j] = Grid[i][j] + displacedFactorsForKTimes[i][j];
        }
      }
      // printGrid("Displaced Grid", dimension, dimension, displacedGrid);

      //Sygkrisi me stoixeia tis kampulis
      double ** newCurvePoints =  new double*[noofPointsInCurve];
      for(int i = 0; i < noofPointsInCurve; i++){
            newCurvePoints[i] = new double[(int)dimension];
      }

      for(int i = 0; i < noofPointsInCurve ; i++){
        for(int j = 0; j < (int)dimension; j++){ // gia kathe stili - aksona
          int curElemPosition = i;
          int axis = j;
          newCurvePoints[i][j] = findMinPointInAnyAxis(dimension, axis, curvePoints[curElemPosition][axis], displacedGrid);

        }
      }
      // printGrid("New Curve Grid", noofPointsInCurve, dimension, newCurvePoints);

      singleVecNoDublicates.clear();
      removeDuplicates(&singleVecNoDublicates, newCurvePoints, dimension, &noofPointsInCurve);
      //cout << " SINGLE before concat" <<endl;
      // printVector(&singleVecNoDublicates);
      //cout << " SINGLE after concat" <<endl;
      Concatenation(&singleVecNoDublicates, &all_K_gridCurvesVecNoDublicates);
       //printVector(&singleVecNoDublicates);
       //printGrid("New Curve Grid without Dublicates", noofPointsInCurve, dimension, newCurvePoints);

      //  cout << "BUCK:: " << endl;
      //  HashArray[l]-> printBucket(l);


      free(newCurvePoints);
      free(displacedGrid);
    }
    //cout << " K grid Curves are" << endl;
    //printVector(&all_K_gridCurvesVecNoDublicates);

    Element* hashElement = new Element(curve_id, &all_K_gridCurvesVecNoDublicates);

    int hashKey;
    if(!details -> typeOfHashChoice.compare("classic")){

      hashKey = FindHashValue(&all_K_gridCurvesVecNoDublicates);

    }
    else{
      vector<double> concatKVecHashFunc;
      vector<double> singleHashFuncVec;

      for(int i = 0 ; i < K_VEC ; i++){
          singleHashFuncVec.clear();
          createVecFunc(dimension, &all_K_gridCurvesVecNoDublicates, &singleHashFuncVec);
          Concatenation(&singleHashFuncVec, &concatKVecHashFunc);
      }

      hashKey = FindHashValue(&concatKVecHashFunc);

    }
  /*  cout << "Xasarw me kleidi: " << hashKey << endl;
    cout << "Eftiaksa R: ";
    for (int i = 0; i < rVector.size(); i++)
    {
      cout << rVector[i] << " ";
    }
    cout << endl;
    */
    HashArray[l]->put(hashKey, hashElement); // eisagwgi se hash table*/
  }
  free(Grid);
}
