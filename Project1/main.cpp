#include <iostream>
#include "file.hpp"
#include "liste.hpp"
#include "listePile.hpp"
using namespace std;
int main() {

    // Déclaration d'une file d'entiers
    
    
    
    

    
    
    // Ajouter des éléments à la file
   
    
    //liste<int> myList;

    //myList.insert(5);
    //myList.insert(6);
    //myList.insert(7);
    //myList.insert(8);
    //myList.insert(9);

    //cout << myList.size() << endl;

    
    //myList.end();
    //cout << myList.value() << endl;
    listePile<int> myList;

    // Insert elements
    myList.insert(7,3); // List: 1
    myList.insert(5,2); // List: 1 2
    myList.insert(1,0); // List: 1 2 3

    myList.print(cout);
    

    

    

   

    // Print the list
    

   
    

    
    
  

    
    

    
    
    return 0;
}
