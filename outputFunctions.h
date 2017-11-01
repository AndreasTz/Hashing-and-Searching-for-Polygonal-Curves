#ifndef OUTPUTFUNCTIONS__H
#define OUTPUTFUNCTIONS__H

#include <vector>
#include <string>
#include "HelpClasses.h"


void OrderNNResult(vector<string>& vec);
void writingToOutputFile(string Filename, vector<queryDetails>& queryOfVec, vector<stats>& vecOfStats ,PreferedDetails &details);
#endif
