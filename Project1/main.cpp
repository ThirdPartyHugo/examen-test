#include <iostream>
#include "file.hpp"
#include "liste.hpp"
#include "listePile.hpp"
#include "doubleFile.hpp"
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
    

    deque<int> d;
    d.push_front(1);
    d.push_front(0);
    d.push_front(2);

    std::cout << "Size: " << d.size() << std::endl; // Output: Size: 3
    std::cout << "Front: " << d.front() << std::endl; // Output: Front: 0
    std::cout << "Back: " << d.back() << std::endl; // Output: Back: 2

   
    std::cout << "Front after pop_front(): " << d.front() << std::endl; // Output: Front after pop_front(): 1

    
    std::cout << "Back after pop_back(): " << d.back() << std::endl; // Output: Back after pop_back(): 1

    cout << d.at(0);


    // Insert elements
  
    

    
    
}
