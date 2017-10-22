#include <iostream>
#include <cmath>
#include <vector>

#include "Hashing.h"
#include "HelpClasses.h"
#include "Grid.h"

using namespace std;

vector<int> rVector;

void addtoR(vector<int>* v, int d)
{
  while (d)
  {
    v->push_back((rand() / (RAND_MAX + 1.0)));
    d--;
  }
}

void deleteR(vector<int>* v)
{
  v->clear();
}

int FindHashValue(vector<double>* concVector)
{
  if (rVector.size() < concVector->size())
  {
    addtoR(&rVector, (rVector.size() - concVector->size()));
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
int selectUniformlyRandomT(double dimension){

  double max = 0.0;
  double min = pow((double)dimension *1.0 , (double)dimension *1.0);
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
void removeDuplicates(vector<double>* vecWithoutDublicates, double **newCurvePoints, double dimension ,int noofPointsInCurve){

  int flag = 0 ;
  int k =0;
  int count =0; //poses fores vrika dublicate

  for(int i = 1 ; i < noofPointsInCurve; i++ ){

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
        for(int k = i-count; k < noofPointsInCurve-1; k++) {
          for(int j = 0; j < dimension; j++) {

             newCurvePoints[k][j] = newCurvePoints[k+1][j];

            }
        }

        count++;

      }
    }
      flag = 0;
  }

  for(int i = 0 ; i < noofPointsInCurve -count;i++){
    for(int j = 0 ; j < (int)dimension ; j++){
      vecWithoutDublicates->push_back(newCurvePoints[i][j]);
      }
    }

  }


/*
Sunartisi i opoia ektypwnei ta simeia tou ekastwte grid
  input : typeOfGrid (Xrisimopoieitai kyriws gia tin ektypwsi tou eidous tou grid pou epilegoume na ektypwthei)
          noofRows (To plithos twn grammwn tou epilegomenoy pinaka)
          noofCols (To plithos twn stilwn tou epilegomenoy pinaka)
          printableGrid (O pinakas pou theloume na ektypwthei)
  output : -
*/
void printGrid(string typeOfGrid, int noofRows ,int noofCols ,double ** printableGrid){

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
void selectT_Vector(vector<double>* t, double dimension){
  t->push_back(selectUniformlyRandomT(dimension));

  int newt;
  for(int i = 1; i < (int)dimension; i++){ //gia kathe diastasi

    newt = selectUniformlyRandomT(dimension);
    t->push_back(newt);

  }
  printVector(t);
}


/*
Synartisi i opoia vazei ola ta simeia mias grid curve se ena pio geniko vector pou periexei ta simeia kai twn K grid curve pou apaitountai
  input : singleVecNoDublicates (vector me ta simeia tis MIAS grid-curve)
          all_K_gridCurvesVecNoDublicates (vector me ta simeia twn K grid curves)
  output : -
*/
void concatAnotherGridCurve(vector<double> *singleVecNoDublicates, vector<double> * all_K_gridCurvesVecNoDublicates){
  double elem;
  for(int i = 0 ; i < singleVecNoDublicates->size(); i++){
    elem = singleVecNoDublicates->back();
    singleVecNoDublicates->pop_back();
    all_K_gridCurvesVecNoDublicates -> push_back(elem);
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
void operation(double dimension, int R, double ** curvePoints , int noofPointsInCurve , HashMap ** const HashArray, PreferedDetails * const details, vector<vector<double>>* v){

  //printGrid("Initial Curve", noofPointsInCurve ,dimension ,curvePoints);
  vector<double> initialCurveNoDublicatesVec;
  removeDuplicates(&initialCurveNoDublicatesVec, curvePoints, dimension, noofPointsInCurve);
  v->push_back(initialCurveNoDublicatesVec);

  int delta =  4*(int)dimension*R; //*min(curve_i)

  double ** Grid = new double* [(int)dimension];
  for(int i = 0; i < (int)dimension; i++){
      Grid[i] = new double[(int)dimension];
  }

  for(int i=0 ; i < (int)dimension; i++){
    for(int j = 0  ; j < (int)dimension; j++ ){
      Grid[i][j] = i * delta;
    }
  }

  vector<double> displacedFactor;
  vector<double> singleVecNoDublicates;
  vector<double> all_K_gridCurvesVecNoDublicates;

  for(int l = 0; l < details->numberOfHashingArrays; l++){  //L- fores
    for(int i = 0; i < details->numberOfLocalitySensitiveFunctions; i++){  //k- fores

      displacedFactor.clear();
      selectT_Vector(&displacedFactor, dimension);

      double ** displacedGrid = new double* [(int)dimension];

      for(int i = 0; i < (int)dimension; i++){
          displacedGrid[i] = new double[(int)dimension];
      }

      for(int i=0 ; i < (int)dimension ;i++){
        for(int j = 0  ; j < (int)dimension ; j++ ){
          displacedGrid[i][j] = Grid[i][j] + displacedFactor[j];
        }
      }
      //printGrid("Displaced Grid", dimension, dimension, displacedGrid);

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
      //printGrid("New Curve Grid", noofPointsInCurve, dimension, newCurvePoints);

      singleVecNoDublicates.clear();
      removeDuplicates(&singleVecNoDublicates, newCurvePoints, dimension, noofPointsInCurve);

      concatAnotherGridCurve(&singleVecNoDublicates, &all_K_gridCurvesVecNoDublicates);

      //printGrid("New Curve Grid without Dublicates", noofPointsInCurve, dimension, newCurvePoints);

      //  cout << "BUCK:: " << endl;
      //  HashArray[l]->printBucket(l);


      free(newCurvePoints);
      free(displacedGrid);
    }
    cout << " K grid Curves are" << endl;
    printVector(&all_K_gridCurvesVecNoDublicates);

    int id = 0;
    Element* hashElement = new Element(id, &all_K_gridCurvesVecNoDublicates);
    int hashKey = FindHashValue(&all_K_gridCurvesVecNoDublicates);
    HashArray[l]->put(hashKey, hashElement); // eisagwgi se hash table*/
  }
  free(Grid);
}

/*void addtoR(vector<int>* v, int d)
{
  while (d)
  {
    v->push_back((rand() / (RAND_MAX + 1.0)));
    d--;
  }
}

void deleteR(vector<int>* v)
{
  v->clear();
}*/
