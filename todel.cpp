#include <iostream>
#include <vector>


using namespace std;


struct subject {
    string name;
    int marks;
    int credits;
};


int main() {
    vector<subject> sub;

    //Push back new subject created with default constructor.
    sub.push_back(subject());

    //Vector now has 1 element @ index 0, so modify it.
    sub[0].name = "english";

    //Add a new element if you want another:
    sub.push_back(subject());

    //Modify its name and marks.
    sub[1].name = "math";
    sub[1].marks = 90;

    for(int i = 0 ; i < sub.size(); i++){
      cout << sub[i].name << endl;
      cout << sub[i].marks << endl;
    }
}
