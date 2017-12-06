#include <fstream>
#include <iterator>
#include <algorithm>

#include "Reading.h"
#include "PreRangeSearch.h"

#define minus_i "-i"
#define minus_c "-c"
#define minus_o "-o"
#define minus_d "-d"
#define minus_complete "-complete"

using namespace std;

extern int dimension ;
extern int NoofCurves;


void readingFromCMD(int howManyArgs, char *argv[] , PreferedDetails& details) {

	string arg;

  if(howManyArgs != 9) {
    cerr << "Wrong number of arguments" << endl;
    exit(-2);
  }


  for(int i = 1 ; i < howManyArgs ; i+=2){
    arg = argv[i];

		if(!arg.compare(minus_i)){
      details.setInputFile(argv[i+1]);

		}
		else if(!arg.compare(minus_c)){
      details.setConfigurationFile(argv[i+1]);

		}
		else if(!arg.compare(minus_o)){
      details.setOutputFile(argv[i+1]);

		}
		else if(!arg.compare(minus_d)){
      details.setMetric(argv[i+1]);

		}
		else if(!arg.compare(minus_complete)){
			details.CompleteParamIShere  = 1;
			}
	  else{
	      cout << "Wrong args!" << endl;
	    }

	}

}


void readingConfFile(string fileName, Parameters& params){

  string line;
  string numStr;
  int num;
   ifstream myfile ;
   myfile.open(fileName);
   if (myfile.is_open())
   {
     while (! myfile.eof() )
     {
       getline (myfile,line);
       cout << line <<endl;
       if(strstr(line.c_str(),"number_of_clusters")){
         numStr = line.substr(20, line.length() - 20);
         num = atoi(numStr.c_str());
         params.setNoofClusters(num);

       }
       else if(strstr(line.c_str(),"number_of_grid_curves")){
         numStr = line.substr(22, line.length() - 22);
         num = atoi(numStr.c_str());
         params.setNoofGridCurves(num);
       }
       else if(strstr(line.c_str(),"number_of_hash_tables")){
         numStr = line.substr(22, line.length() - 22);
         num = atoi(numStr.c_str());
         params.setNoofHT(num);
       }

     }
     myfile.close();
   }

   else cout << "Unable to open file";
}



void OpenFile(ifstream& myfile, string Filename)
{
  myfile.open(Filename);
  if(!myfile.is_open()){
    cerr << " Problem in openning the file you've asked " << endl;
    exit(-2);
  }

}


int EstimateDimensions(ifstream& myfile){

  string firstLineOfFile;

  if(myfile.is_open()){

    getline(myfile,firstLineOfFile);
    int dimension;
    if(firstLineOfFile.length() == 10){ // den exei allo orisma einai mono @dimension

      dimension = 2;

    }
    else{

      string dimStr = firstLineOfFile.substr (11,firstLineOfFile.length() - 11);
      dimension = atoi(dimStr.c_str());

    }

    return dimension;
  }
  else{
    cerr << " Problem in openning the file you've asked " << endl;
    throw;
    exit(-2);
  }
}


void EstimateCurveDetails(Curve& curve, string Line, int dimension){//, vector<int>& curveNoOfPointsVec){

	static int timesHere = 0;
	curve.curvePlace =timesHere;

	curve.curve_id = strtok ( const_cast<char*> (Line.c_str()),"\t, ");
	string noofPointsInCurveStr =  strtok( 0 , "\t, ");
	curve.noofPointsInCurve = atoi(noofPointsInCurveStr.c_str());

	string pointStr;

  curve.curvePoints = std::vector<std::vector<long double>>(curve.noofPointsInCurve, std::vector<long double>(dimension));
	for(int i = 0; i < curve.noofPointsInCurve ; i++){
		for(int j = 0 ; j < dimension ; j++){

			pointStr = strtok (  0 ,"()\t, ");
			curve.curvePoints[i][j] = stod(pointStr);

		}
	}


	timesHere++;
}


int EstimateTotalLines(ifstream& myfile){

  // new lines will be skipped unless we stop it from happening:*/
  myfile.unsetf(std::ios_base::skipws);

  // count the newlines with an algorithm specialized for counting:
  unsigned line_count = count( istream_iterator<char>(myfile), istream_iterator<char>(), '\n');

  return ((int) line_count);
}


void readingFromFile(ifstream &myfile, vector<vector<vector<long double>>>& AllCurvePoints, int noofHTs, int noofGridCurves, HashMap** HTArray, int type,vector<string>& nameVector){

  Curve curve;
  string Line;

  myfile.clear();
  myfile.seekg(0, ios::beg);

  getline(myfile,Line); //dimension

  AllCurvePoints.clear();

  getline(myfile,Line);

  while(!myfile.eof() && Line.compare("\n")){

    EstimateCurveDetails(curve, Line, dimension);
    //curve.printCurveDetails();
    //Utils::printVectorOfVector(curve.curvePoints);

    removeDuplicates(curve.curvePoints, dimension, curve.noofPointsInCurve);

    AllCurvePoints.push_back(curve.curvePoints);
		nameVector.push_back(curve.curve_id);
		
		PreRangeSearch(curve, noofHTs, noofGridCurves, HTArray, type);

    getline(myfile,Line);

  }

}
