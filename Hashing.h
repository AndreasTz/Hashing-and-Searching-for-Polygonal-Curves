#ifndef HASHING__H
#define HASHING__H

#include <iostream>
#include <vector>

using namespace std;

const int TABLE_SIZE = 101;
const int M = 1000000;

struct Element
{
  int ID;
  string mName;
  vector<long double> gC;
  int assigned;

  Element(): assigned(0) {}
  
  void setAssignment(int assignMType)
  {
    this->assigned = assignMType;
  }
};

class HashMap {

private:
      vector<vector<Element> > mTable;

public:
      HashMap() : mTable(TABLE_SIZE) {}

      unsigned getHash(unsigned key) const
      {
          return key % M % TABLE_SIZE;
      }

      const Element& getFirstElement(int key) const
      {
          if (isEmpty(key))
          {
              throw key;
          }

          return mTable[getHash(key)][0];
      }

      Element& getFirstElement(int key)
      {
          if (isEmpty(key))
          {
              throw key;
          }

          return mTable[getHash(key)][0];
      }

      bool isEmpty(unsigned key) const
      {
        return mTable[getHash(key)].size() == 0;
      }

      void put(int key, Element elem)
      {
          /*std::cout << elem.ID << '\n';
          if (elem.gC.empty())
          {
              std::cout << "[]" << '\n';
          }
          else
          {
              std::cout << "[";
              for (auto x : elem.gC)
              {
                  std::cout << x << ", ";
              }
              std::cout << "\b\b]" << '\n';
          }*/
          mTable[getHash(key)].emplace_back(std::move(elem));
      }

      const vector<Element>& getBucket(unsigned key) const
      {
          return mTable[getHash(key)];
      }


};

#endif
