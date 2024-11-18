#include "pile.hpp"
#include <iostream>


template <class TYPE>
class listePile {
private:
    stack<TYPE> _gauche;  // Left stack
    stack<TYPE> _droite;  // Right stack

public:
    listePile();  // Constructor
    ~listePile(); // Destructor

    bool empty() const;    // Returns true if the list is empty
    void clear();          // Clears the list
    void next();           // Moves the cursor to the next position
    void previous();       // Moves the cursor to the previous position
    void begin();          // Positions the cursor at the beginning
    void end();            // Positions the cursor at the end
    bool isBegin() const;  // Checks if at the beginning
    bool isEnd() const;    // Checks if at the end
    TYPE& value() const;   // Returns the value at the cursor
    int size() const;      // Returns the number of elements
    void insert(const TYPE& element, const TYPE& element2); // Inserts before the cursor
    void erase();          // Deletes the element at the cursor
    void print(std::ostream& out);    // Prints the list
    const listePile& operator=(const listePile& l); // Assignment operator
};

// Implementation of methods

template <class TYPE>
listePile<TYPE>::listePile() {
    // Stacks are initialized by default
}

template <class TYPE>
listePile<TYPE>::~listePile() {
    clear();
}

template <class TYPE>
bool listePile<TYPE>::empty() const {
    return _gauche.empty() && _droite.empty();
}

template <class TYPE>
void listePile<TYPE>::clear() {
    _gauche.clear();
    _droite.clear();
}

template <class TYPE>
void listePile<TYPE>::next() {
    if (!_droite.empty()) {
        // Move top of _droite to _gauche
        _gauche.push(_droite.top());
        _droite.pop();
    }
    // If _droite is empty, cursor is at the end; do nothing
}

template <class TYPE>
void listePile<TYPE>::previous() {
    if (_droite.empty() && !_gauche.empty()) {
        // Cursor is at the end; move last element from _gauche to _droite
        _droite.push(_gauche.top());
        _gauche.pop();
    }
    else if (!_gauche.empty()) {
        // Move top of _gauche to _droite
        _droite.push(_gauche.top());
        _gauche.pop();
    }
    // If _gauche is empty, cursor is at the beginning; do nothing
}

template <class TYPE>
void listePile<TYPE>::begin() {
    // Move all elements from _gauche to _droite
    while (!_gauche.empty()) {
        _droite.push(_gauche.top());
        _gauche.pop();
    }
}

template <class TYPE>
void listePile<TYPE>::end() {
    // Move all elements from _droite to _gauche
    while (!_droite.empty()) {
        _gauche.push(_droite.top());
        _droite.pop();
    }
}

template <class TYPE>
bool listePile<TYPE>::isBegin() const {
    return _gauche.empty();
}

template <class TYPE>
bool listePile<TYPE>::isEnd() const {
    return _droite.empty();
}

template <class TYPE>
TYPE& listePile<TYPE>::value() const {
    if (!_droite.empty()) {
        return const_cast<TYPE&>(_droite.top());
    }
    else {
       
    }
}

template <class TYPE>
int listePile<TYPE>::size() const {
    return _gauche.size() + _droite.size();
}

template <class TYPE>
void listePile<TYPE>::insert(const TYPE& element, const TYPE& element2) {
    // Insert before the cursor by pushing onto _gauche
    _gauche.push(element);




    

    // Push the new element onto _droite (which is reversed)
    
    _droite.push(element2);
    // Reverse back into _droite
    
    
    
   

    
}

template <class TYPE>
void listePile<TYPE>::erase() {
    if (!_droite.empty()) {
        // Remove the element at the cursor by popping from _droite
        _droite.pop();
        // Cursor moves to the next element (new top of _droite)
    }
    else {
        // Cannot erase; cursor is at the end
       
    }
}

template <class TYPE>
void listePile<TYPE>::print(std::ostream& out) {
    // Print elements from _gauche in order
    stack<TYPE> temp;
    stack<TYPE> tempGauche = _gauche;

    // Reverse _gauche into temp to get the correct order
    while (!tempGauche.empty()) {
        temp.push(tempGauche.top());
        tempGauche.pop();
    }

    // Print elements from temp (left side)
    while (!temp.empty()) {
        out << temp.top() << " ";
        temp.pop();
    }

    // Print elements from _droite as is (right side)
    stack<TYPE> tempDroite = _droite;

    // Print elements from tempDroite (right side) without reversing
    while (!tempDroite.empty()) {
        out << tempDroite.top() << " ";
        tempDroite.pop();
    }

    out << std::endl;
}


template <class TYPE>
const listePile<TYPE>& listePile<TYPE>::operator=(const listePile<TYPE>& l) {
    if (this != &l) {
        _gauche = l._gauche;
        _droite = l._droite;
    }
    return *this;
}
