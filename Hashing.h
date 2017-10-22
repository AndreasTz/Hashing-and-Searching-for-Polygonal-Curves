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

  Element(int id, vector<double>* g)
  {
    this->ID = id;
    this->gridCurve = g;
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
      }

      ~HashMap()
      {
            for (int i = 0; i < TABLE_SIZE; i++)
                  if (table[i] != NULL)
                        delete table[i];
            delete[] table;
      }
};









#endif
