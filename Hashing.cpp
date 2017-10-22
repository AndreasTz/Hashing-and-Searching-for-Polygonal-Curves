#include <iostream>
#include <vector>
#include "Hashing.h"

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
