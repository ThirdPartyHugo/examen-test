#include <iostream>
#include <queue>
#include "file.hpp"
#include "liste.hpp"
using namespace std;
int main() {

    // D�claration d'une file d'entiers
    
    
    
    

    
    
    // Ajouter des �l�ments � la file
   
    
    liste<int> myList;

    myList.insert(5);
    myList.insert(6);
    myList.insert(7);
    myList.insert(8);
    myList.insert(9);

    //cout << myList.size() << endl;

    
    myList.end();
    cout << myList.value() << endl;


    

    
    
  

    
    

    
    
    return 0;
}
