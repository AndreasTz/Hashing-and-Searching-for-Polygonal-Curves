#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#include "Hashing.h"
#include "HelpClasses.h"
#include "Grid.h"
#include "frechet.h"


#define delta 1
#define K_VEC 3

using namespace std;

vector<int> rVector;
void ExhaustiveSearch(vector<vector<double>>& curveVector, vector<string>& nameVector, vector<double>& qVector, queryDetails& QD)
{
	double TrueDistance = FrechetDistance(curveVector[0], qVector, 1);

  QD.LSHDistance = QD.trueDistance = TrueDistance;
  QD.LSHNearestNeighbor = QD.trueNearestNeighbor = nameVector[0];

  for (unsigned i = 0; i < curveVector.size(); ++i)
  {
  	if (TrueDistance > FrechetDistance(curveVector[i], qVector, 1))
  	{
	    TrueDistance = FrechetDistance(curveVector[i], qVector, 1);
	  	QD.LSHDistance = QD.trueDistance = TrueDistance;
	    QD.LSHNearestNeighbor = QD.trueNearestNeighbor = nameVector[i];
	  }
  }
}

//INPUT 2 vector<double>
//OUTPUT: true if they are equal, false otherwise!

bool CompareVectors(const vector<double>& v1, const vector<double>& v2)
{
  if (v1.size() != v2.size()) return false;
  for (unsigned i; i < v1.size(); ++i)
  {
    if (v1[i] != v2[i]) return false;
  }
  return true;
}

//pretified for element data struct
bool CompareHashElementVectors(const Element& ele1, const Element& ele2)
{
  return CompareVectors(ele1.gC, ele2.gC);
}

//adding size to Rvector when needed
void addtoR(vector<int>& v, int d)
{
  while (d)
  {
    v.push_back((rand() % 101));
    //cout << "RANDOM EINAI:: " << v->back() << endl;
    d--;
  }
}

//INPUT v<d>*
//OUTPUT int type hashValue (which will be changed to index in Hashing.cpp functions)
int FindHashValue(const vector<double>& concVector)
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


/*
Sunartisi i opoia upologizei kai epistrefei enan tyxaio arithmo (me vasi tin omoiomorfi katanomi) gia tin dimiourgia tyxaiwn metatopismenwn grid
  input : dimension (diastasi tis kampilis)
  output : tyxaios arithmos apo tin omoiomorfi katanomi
*/
double selectUniformlyRandomT(double maxValue){

  double min = 0.0;
  double max = maxValue ;
  return min + (double) ((max-min+1.0) * (rand() / (RAND_MAX + 1.0)));
}


/*
Synartisi i opoia upologizei to "kontinotero simeio"  enos simeiou tis dotheisas kampilis me to antistoixo grid
O upologismos ginetai simeio simeio gia kathe aksona ksexorista.
  input : dimension (H diastasi tis kampilis)
          curvePoint (Simeio se aksona)
          displacedGrid
  output : minElem (To kontinotero simeio tou grid)
*/
double findMinPointInAnyAxis(double dimension, int axis, double curvePoint, const vector<vector<double>>& displacedGrid){

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
void removeDuplicates(vector<double>& vecWithoutDublicates, vector<vector<double>>& newCurvePoints, double dimension ,int& noofPointsInCurve){

  int flag = 0 ;
  int count =0; //poses fores vrika dublicate

  int timesForLoop = noofPointsInCurve;
  for(int i = 1 ; i < timesForLoop; i++ ){

    int thesi = i - count;

    if(newCurvePoints[thesi - 1][0] == newCurvePoints[thesi][0] ){
      flag++ ;

      for(int j = 1 ; j < ((int)dimension) - 1; j++){

        if(newCurvePoints[thesi-1][j] == newCurvePoints[thesi][j] ){
          flag++;
        }

      }

      if(flag == ((int) dimension) -1){
        //cout << " We have a dublicate!  " << endl;
        noofPointsInCurve--;

        for(int k = i-count; k < noofPointsInCurve; k++) {
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
      vecWithoutDublicates.push_back(newCurvePoints[i][j]);
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
void  printGrid(const string& typeOfGrid, int noofRows ,int noofCols ,double ** printableGrid){

    cout <<  typeOfGrid  << endl;
    for(int i=0 ; i < noofRows ;i++){
      for(int j = 0  ; j < noofCols ; j++ ){
        cout << printableGrid[i][j] << " ";
      }
      cout << endl;
    }

}


/* Sunartisi ektipwsis vector*/
void printVector(const vector<double>& t){
  cout << "VECTOR: " << endl;
  for (double i : t)
    cout << i << ' ';
  cout << " ***" << endl;
}


/*
Synartisi epilogis tyxaiou vector pros metatopisi
*/
void selectT_Vector(vector<double>& t, double lenOfVec){
  t.push_back(selectUniformlyRandomT(lenOfVec));

  int newt;
  for(int i = 1; i < (int)lenOfVec; i++){ //gia kathe diastasi

    newt = selectUniformlyRandomT(lenOfVec);
    t.push_back(newt);

  }
   //printVector(t);
}


/*
Synartisi i opoia vazei ola ta simeia mias grid curve se ena pio geniko vector pou periexei ta simeia kai twn K grid curve pou apaitountai
  input : singleVec (vector me ta simeia tis MIAS grid-curve)
          resultVec (vector pou ginetai concat)
  output : -
*/
void Concatenation(vector<double>& singleVec, vector<double>& resultVec){
  double elem;

  int sizeOfVec = singleVec.size();
  for(int i = 0 ; i < sizeOfVec; i++){
    elem = singleVec.back();
    singleVec.pop_back();
    resultVec.push_back(elem);
  }
}


/*
Sunartisi i opoia epistrefei enan arithmo apo kanoniki katanomi me vasi tin methodo Marsaglia twn diafaneiwn
*/
double selectFromNormalDistr() {

  static int count = 0;
  static double nextGaussianVal;
  double firstGaussianVal, val1, val2, s;

 if (count == 0) {
    do {
        val1 = 2 * ((double) rand() / (RAND_MAX)) - 1;  // between -1.0 and 1.0
        val2 = 2 * ((double) rand() / (RAND_MAX)) - 1;  // between -1.0 and 1.0
        s = val1 * val1 + val2 * val2;
     } while (s >= 1 || s == 0);
     const double multiplier = sqrt(-2 * log(s)/s);
     nextGaussianVal = val2 * multiplier;
     firstGaussianVal = val1 * multiplier;
     count = 1;
     return firstGaussianVal;
 }

 count = 0;
 return abs(nextGaussianVal);
}


/*
Sunartisi i opoia apo ena vector briskei ena simeio
input : dimension(diastasi simeiou)
        resultVec (vector apothikeysis apotelesmatos)
        all_K_gridCurvesVecNoDublicatesCP (vector pou periexei kai tis k kampiles plegmatos )
output: -
*/
void findPoint(double dimension, vector<double>& resultVec, vector<double>& all_K_gridCurvesVecNoDublicatesCP){
  double Elem;
  resultVec.clear();
  for(int i = 0; i < dimension ; i++){

    Elem = all_K_gridCurvesVecNoDublicatesCP.back();
    all_K_gridCurvesVecNoDublicatesCP.pop_back();
    resultVec.push_back(Elem);
  }
}


/*synartisi i opoia upologizei to eswteriko ginomeno duo dianismatwn
Exei ginei mia mikri parallagi vevaia gia tin periptwsi pou ta dianismata den exoun to idio megethos
Eisagoume ston vector vec2 (alliws v tou projection) epipleon stoixeia mono an |vec1| > |vec2|
Giati theoroume oti to v prepei na simvadizei me to megalitero dianisma
*/
double multiplyVectors(const vector<double>& vec1, vector<double>& vec2){
  double result = 0.0;

  if(vec1.size() > vec2.size()){ //Prepei na auksisoyme to megethos tou vector v
    for(unsigned j = 0 ; j < vec1.size() - vec2.size(); ++j){
      vec2.push_back(selectFromNormalDistr());
    }
  }

//Exoume 2 theoritika isomegethi dianusmata
  for(unsigned i = 0 ; i < vec1.size() ; ++i){
    result = result + (vec1[i]* vec2[i]);
  }
  return result;
}

/*
Synartisi i opoia ypologizei to euklideio has
me basi twn tipo h= floor((point * v + t) /w)
  input : dimension(diastasi twn simeiwn)
          all_K_gridCurvesVecNoDublicates (to concat twn k grid-curve)
          singleHashFuncVec (to apotelesma)
  output : -
*/
void createVecFunc(double dimension, vector<double>& all_K_gridCurvesVecNoDublicates, vector<double>& singleHashFuncVec){
  vector<double> v;
  vector<double> tempResultVec;

  const int w = 4;
  double swiftFactor;
  double multRes;
  double sum;
  double divRes;
  int total;

  for(unsigned i = 0 ; i < all_K_gridCurvesVecNoDublicates.size(); i++){

//    v.clear();

    swiftFactor = selectUniformlyRandomT((double)w);

    for(int i =0; i < dimension ; i++)
      v.push_back(selectFromNormalDistr());

    tempResultVec.clear();
    findPoint(dimension, tempResultVec, all_K_gridCurvesVecNoDublicates);

    for(unsigned i = 0 ; i < tempResultVec.size(); i++){
      multRes = tempResultVec[i] * v[i];
    }

    sum = multRes + swiftFactor;
    divRes = sum / w;
    total =   floor(divRes);
    singleHashFuncVec.push_back(total);

  }

}


/*
Synartisi i opoia upologizei to mikrotero a_i gia tin dimiourgia tou arxikou Grid
  input : dimension (diastasi simeiwn kampilis)
          displacedFactor (paragontas metatopisis)
          initialCurveNoDublicatesVec (arxiki kampili xwris diplotipa)
  output: minA(to mikrotero a_i)
*/
double findMinA(int dimension, int row ,int col, const vector<vector <double> > displacedFactor, const vector<double>& initialCurveNoDublicatesVec){

  double *a = new double [initialCurveNoDublicatesVec.size()];
  double diff = initialCurveNoDublicatesVec[row] - displacedFactor[row][0];
  if(diff < 0){
    diff = diff * (-1);
  }

  a[0] = diff / delta;

  double minA = a[0];
  for(int i =1 ; i < dimension; i++){
    diff = initialCurveNoDublicatesVec[col] - displacedFactor[row][i];
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
void fillGrid(int dimension, int noofPointsInCurve, int numberOfLocalitySensitiveFunctions, vector< vector<double> >& vectorOfVectors ,vector<double>& initialCurveNoDublicatesVec, vector<vector<double>>& Grid){

  for(int i = 0; i < numberOfLocalitySensitiveFunctions; i++){
    vector<double> rowVec;
    selectT_Vector(rowVec, dimension);
    vectorOfVectors.push_back(rowVec);
  }
  double value;
  for(int i=0 ; i < (int)dimension; i++){
    for(int j = 0  ; j < (int)dimension; j++ ){
       value = (j+1)* findMinA(dimension, i, j, vectorOfVectors , initialCurveNoDublicatesVec );
       Grid[i][j] = floor(value);
    }
  }
}


void createInitialCurveNoDublicates(int dimension, vector<vector<double>>& curvePoints, int noofPointsInCurve, vector<vector<double>>& v, vector<double>& initialCurveNoDublicatesVec){
    removeDuplicates(initialCurveNoDublicatesVec, curvePoints, dimension, noofPointsInCurve);
    v.push_back(initialCurveNoDublicatesVec);
}


/*
*/
void PrepareForLSH(double dimension,
                   vector<double>& all_K_gridCurvesVecNoDublicates,
                   vector<double>& initialCurveNoDublicatesVec,
                   const PreferedDetails& details,
                   std::vector<std::vector<double>>& curvePoints,
                   int noofPointsInCurve)
{
  vector<vector<double>> Grid((int)dimension, vector<double>((int)dimension));

  vector< vector<double> > displacedFactorsForKTimes;
  fillGrid(dimension, details.numberOfLocalitySensitiveFunctions, noofPointsInCurve, displacedFactorsForKTimes, initialCurveNoDublicatesVec, Grid);

  vector<double> singleVecNoDublicates;
  for(int i = 0; i < details.numberOfLocalitySensitiveFunctions; i++){  //k- fores
    vector<vector<double>> displacedGrid((int)dimension, vector<double>((int)dimension));
    for(int i=0 ; i < (int)dimension ;i++){
      for(int j = 0  ; j < (int)dimension ; j++ ){
        displacedGrid[i][j] = Grid[i][j] + displacedFactorsForKTimes[i][j];
      }
    }
    // printGrid("Displaced Grid", dimension, dimension, displacedGrid);

    //Sygkrisi me stoixeia tis kampulis
    vector<vector<double>> newCurvePoints(noofPointsInCurve, vector<double>((int)dimension));

    for(int i = 0; i < noofPointsInCurve ; i++){
      for(int j = 0; j < (int)dimension; j++){ // gia kathe stili - aksona
        int curElemPosition = i;
        int axis = j;
        newCurvePoints[i][j] = findMinPointInAnyAxis(dimension, axis, curvePoints[curElemPosition][axis], displacedGrid);
      }
    }
    // printGrid("New Curve Grid", noofPointsInCurve, dimension, newCurvePoints);

    singleVecNoDublicates.clear();
    removeDuplicates(singleVecNoDublicates, newCurvePoints, dimension, noofPointsInCurve);
    Concatenation(singleVecNoDublicates, all_K_gridCurvesVecNoDublicates);

  //cout << " K grid Curves are" << endl;
  //printVector(&all_K_gridCurvesVecNoDublicates);
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
void Operation(int curve_id, double dimension, HashMap ** const HashArray, const PreferedDetails& details, vector<double>& initialCurveNoDublicatesVec, int noofPointsInCurve, std::vector<std::vector<double>>& curvePoints, int type, vector<queryDetails>& queryOfVector, vector<vector<double>>& gridCurve, vector<string>& nameVector){

  static int curveID = 0;
  int hashKey;

  for(int l = 0 ; l < details.numberOfHashingArrays ; l++){ //LSH : ekteleitai to loop L-fores

    vector<double> all_K_gridCurvesVecNoDublicates;
    /*h sunartisi dimiourgei k- grid curves kai tis topothetei sto antistoixo vector*/
    PrepareForLSH( dimension, all_K_gridCurvesVecNoDublicates, initialCurveNoDublicatesVec, details, curvePoints , noofPointsInCurve);

    if(!details.typeOfHashChoice.compare("probabilistic")){  //exoume enan pinaka katakermatismou
      vector<double> concatKVecHashFunc; //vector pou periexei tis kvec hashFunctions
      vector<double> singleHashFuncVec; //vector pou periexei 1 hashFunction kathe fora

      /*evresi euklideias LSH sunartisis*/
      for(int i = 0 ; i < K_VEC ; i++){
        singleHashFuncVec.clear();
        createVecFunc(dimension, all_K_gridCurvesVecNoDublicates, singleHashFuncVec);
        Concatenation(singleHashFuncVec, concatKVecHashFunc);
      }
      hashKey = FindHashValue(concatKVecHashFunc);
    }
    else{
      hashKey = FindHashValue(all_K_gridCurvesVecNoDublicates);
    }

    if(type == 1){ //an einai input File
      /*Topothetisi sto hash table*/
      HashArray[l]->put(hashKey, {curveID, "k", all_K_gridCurvesVecNoDublicates});
    }
    else{ //an einai query File

      //initializing queryDetails
      queryDetails QD;

      vector<int> IDmatchVectorTEST;

      for (auto& x : HashArray[0]->getBucket(hashKey))
      {
        if (x.gC == all_K_gridCurvesVecNoDublicates)
        {
      	  IDmatchVectorTEST.push_back(x.ID);
      	  cout << "WE FOUND ONE!" << endl;
          QD.foundGridCurve = true;
      	}
      }

      //if we find no grid matches in bucket we brute force!
      if (QD.foundGridCurve == false)
      {	cout << nameVector.size() << endl;
        ExhaustiveSearch(gridCurve, nameVector, all_K_gridCurvesVecNoDublicates, QD);
      }
      else
      {
         for (unsigned i; i < IDmatchVectorTEST.size(); ++i)
         {
             cout << "KLEO NTAKS@@ : " << IDmatchVectorTEST[i] << endl;
         }
        //TargettedSearch(..);
      }
    }
  }
  curveID++;
}
