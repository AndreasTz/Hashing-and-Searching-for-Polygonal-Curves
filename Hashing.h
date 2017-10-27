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
  vector<double>* gridCurve;
  vector<double> gC;

  Element(int id, vector<double>* g)
  {
    this->ID = id;
    cout << "EVALA TO ********:: " << g->size() << endl;
    //cout << "EVALA TO ********:: " << this->gridCurve[0][0] << endl;
    for (int i = 0; i < g->size(); i++)
    {
      this->gC.push_back(g[0][i]);
    }
    this->gridCurve = &gC;
  }
};


class HashEntry {

private:

      int key;
      Element* element;

public:

      HashEntry* next;

      HashEntry(int key, Element* elem)
      {
            this->key = key;
            this->element = elem;
            this->next = NULL;
      }

      int getKey()
      {
            return this->key;
      }

      Element* getElement()
      {
            return this->element;
      }

      vector<double>* getVector()
      {
        return this->element->gridCurve;
      }

      int getID()
      {
        return this->element->ID;
      }

      void PrintGridCurve()
      {
        cout << "To gridCurve me ID:: " << element->ID << " einai: " << endl;
        //cout << "TO SIZE EINAI::::::: " << element->gridCurve->size();
        cout << "TO SIZE EINAI::::::: " << this->element->gridCurve->size() << endl;
        for (int i = 0; i < element->gridCurve->size(); i++)
        {
          cout << element->gridCurve[0][i] << " ";
        }
        cout << endl;
      }

      void nuke()
      {
        free(this->element);
      }
};

class HashMap {

private:

      HashEntry **table;

public:

      HashMap()
      {

            table = new HashEntry*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
                table[i] = NULL;
      }

      Element* getFirstElement(int key)
      {
            int hash = (key % M % TABLE_SIZE);
            if (table[hash] != NULL)
            {
              return table[hash]->getElement();
            }
      }

      int isEmpty(int key)
      {
        int hash = (key % M % TABLE_SIZE);
        if (table[hash] == NULL) return 1;
        return 0;
      }

      void printBucketArray(int key)
      {
        if (isEmpty(key)) cout << "This point to an empty bucket!" << endl;
        else
        {
          int hash = (key % M % TABLE_SIZE);
          cout << "******************************" << endl;
          for (int i = 1; i < table[hash]->getElement()->gridCurve->size(); i++)
          {
            cout << table[hash]->getElement()->gridCurve->size() << " ";
          }
          cout << endl;
          cout << "WEW LAD" << endl;
          HashEntry* curr;
          curr = hash[table];
          while (curr->next)
          {
            cout << "IS NEXT-> NULL???? NOT IF I CAME HERE:: " << endl;
            curr = curr->next;
            for (int i = 1; i < curr->getElement()->gridCurve->size(); i++)
            {
              cout << curr-> getElement()->gridCurve->size() << " ";
            }
            cout << endl;
          }
        }
      }

      void printBucket(int key)
      {
        if (isEmpty(key))
        {
          cout << "This points to an empty bucket!" << endl;
        }
        int hash = (key % M % TABLE_SIZE);
        cout << table[hash]->getElement()->gridCurve->size() << endl;
        HashEntry* curr;
        curr = table[hash];
        while (curr->next)
        {
          curr = curr->next;
          cout << curr->getElement()->gridCurve[0][0] << endl;
        }
      }

      HashEntry* getBucket(int key)
      {
        int hash = (key % M % TABLE_SIZE);
        return table[hash];
      }

      void put(int key, Element* elem)
      {
            //TESTING ONLY
            cout << "TO KEY EINAI:: " << key << endl;
            cout << "TO VECTOR GRID CONC EINAI:: ";
            for (int i = 0; i < elem->gridCurve->size(); i++)
            {
              cout << elem->gridCurve[0][i] << " ";
            }
            cout << endl;
            cout << "KAI ID:: " << elem->ID << endl;
            //TESTING ONLY

            int hash = (key % M % TABLE_SIZE);
            if (table[hash] == NULL) table[hash] = new HashEntry(key, elem);
            else
            {
              HashEntry* curr;
              curr = hash[table];
              while (curr->next != NULL)
              {
                curr = curr->next;
              }
              HashEntry* kainourgio = curr->next;
              kainourgio = new HashEntry(key, elem);
              curr->next = kainourgio;
            }
            //cout << "PWS ***********************:: " << endl;
            //table[hash]->PrintGridCurve();
      }

      int FindBucket(int key)
      {
        int index = (key % M % TABLE_SIZE);
        return index;
      }

      HashEntry* FirstElementOfBucket(int index)
      {
        return table[index];
      }

      ~HashMap()
      {
            for (int i = 0; i < TABLE_SIZE; i++)
                  if (table[i] != NULL)
                  {
                        table[i]->nuke();
                        free(table[i]);
                  }
      }
};









#endif
