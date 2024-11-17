#include <iostream>
#include <queue>
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
    listePile<int> lst;

    // Add elements to the list
    lst.ajouterApres(10);
    lst.ajouterApres(20);
    lst.ajouterApres(30);

    // Move cursor to the beginning
    lst.debut();

    // Insert before cursor
    lst.ajouterAvant(5);

    // Advance the cursor and get current value
    lst.avancer();
    std::cout << "Current value: " << lst.valeurCourante() << std::endl;

    

    
    
  

    
    

    
    
    return 0;
}
