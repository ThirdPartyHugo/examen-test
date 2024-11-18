#pragma once

template <class TYPE>
class deque {
private:
	// Structure d'une cellule. La double file est composée de plusieurs de ces cellules
	struct cellule {
		TYPE _element; // Donnée enregistrée dans une des cellules de la double-file
		cellule* _next; // Pointeur vers la prochaine cellule de la double file
		cellule* _prev; // Pointeur vers la cellule précédente de la double file

		// Constructeur d'une cellule (méthode appelée à chaque fois qu'on fait un "new Cellule")
		cellule(const TYPE& element, cellule* next, cellule* prev) {
			_element = element;
			_next = next;
			_prev = prev;
		}
	};

	cellule* _deque; // Pointe sur la dernière cellule dont le "next" pointe sur la première

public:
	deque(); // Constructeur qui initialise "_deque" à "nullptr"
	deque(const deque<TYPE>&); // Copieur (pour le désactiver, il faut le placer dans la section "private")
	~deque(); // Destructeur qui supprime toutes les cellules de la double-file

	bool empty() const; // Méthode qui vérifie si la file est vide (retourne true) ou non (retourne false)
	int size() const; // Méthode qui retourne le nombre de cellules que contient la double-file
	void clear(); // Méthode qui supprime toutes les cellules de la double-file

	const TYPE& front() const;
	const TYPE& back() const;

	TYPE pop_front(); // Méthode qui supprime la première cellule de la double-file et retourne son élément par valeur
	TYPE pop_back(); // Méthode qui supprime la dernière cellule de la double-file et retourne son élément par valeur

	void push_front(const TYPE&); // Méthode qui ajoute une nouvelle cellule au début de la double-file
	void push_back(const TYPE&); // Méthode qui ajoute une nouvelle cellule à la fin de la double-file

	const deque<TYPE>& operator=(const deque<TYPE>&); /* Surcharge de l'opérateur = pour copier le contenu d'une
														 double-file vers une autre. */

														 /* ATTENTION : la méthode "at()" et la surcharge de l'opérateur [] contournent l'utilisation
															habituelle d'une double-file, car elles permettent un accès explicite au contenu de chacune
															des cellules, alors que le principe d'utilisation standard d'une double file consiste à
															n'accéder qu'au début (première cellule) ou qu'à la fin (dernière cellule). C'est pourquoi
															on parle alors de structure de données implicite, car on n'a habituellement pas accès à toutes
															les cellules d'une double-file. La méthode "at()" et la surcharge de l'opérateur [] sont
															données pour simplifier l'utilisation de la double-file, mais elles ne devraient en aucun
															cas être considérées comme des méthodes faisant normalement partie de la structure de données
															qu'est la double-file. */
	const TYPE& at(int) const; /* Pour retourner un élément présent à une certaine position dans la double-file,
							   mais sans pouvoir modifier l'élément à cette position (lecture seulement) */
	const TYPE& operator[](int) const;
};



// Default constructor
template<class TYPE>
inline deque<TYPE>::deque() : _deque(nullptr) {}

// Copy constructor
template<class TYPE>
inline deque<TYPE>::deque(const deque<TYPE>& other) : _deque(nullptr) {
    if (!other.empty()) {
        cellule* current = other._deque->_next;
        do {
            push_back(current->_element);
            current = current->_next;
        } while (current != other._deque->_next);
    }
}

// Destructor
template<class TYPE>
inline deque<TYPE>::~deque() {
    clear();
}

// Check if the deque is empty
template<class TYPE>
inline bool deque<TYPE>::empty() const {
    return _deque == nullptr;
}

// Return the number of elements in the deque
template<class TYPE>
inline int deque<TYPE>::size() const {
    if (empty())
        return 0;
    int count = 1;
    cellule* current = _deque->_next;
    while (current != _deque) {
        ++count;
        current = current->_next;
    }
    return count;
}

// Clear the deque
template<class TYPE>
inline void deque<TYPE>::clear() {
    while (!empty()) {
        pop_front();
    }
}

// Access the front element
template<class TYPE>
inline const TYPE& deque<TYPE>::front() const {
    if (empty())
        throw std::out_of_range("Deque is empty");
    return _deque->_next->_element;
}

// Access the back element
template<class TYPE>
inline const TYPE& deque<TYPE>::back() const {
    if (empty())
        throw std::out_of_range("Deque is empty");
    return _deque->_element;
}

// Remove and return the front element
template<class TYPE>
inline TYPE deque<TYPE>::pop_front() {
    if (empty())
        throw std::out_of_range("Deque is empty");

    cellule* frontNode = _deque->_next;
    TYPE element = frontNode->_element;

    if (_deque == frontNode) {
        // Only one element
        delete frontNode;
        _deque = nullptr;
    }
    else {
        _deque->_next = frontNode->_next;
        frontNode->_next->_prev = _deque;
        delete frontNode;
    }
    return element;
}

// Remove and return the back element
template<class TYPE>
inline TYPE deque<TYPE>::pop_back() {
    if (empty())
        throw std::out_of_range("Deque is empty");

    cellule* backNode = _deque;
    TYPE element = backNode->_element;

    if (_deque->_next == _deque) {
        // Only one element
        delete backNode;
        _deque = nullptr;
    }
    else {
        _deque = backNode->_prev;
        _deque->_next = backNode->_next;
        backNode->_next->_prev = _deque;
        delete backNode;
    }
    return element;
}

// Add an element to the front
template<class TYPE>
inline void deque<TYPE>::push_front(const TYPE& element) {
    cellule* newNode = new cellule(element, nullptr, nullptr);

    if (empty()) {
        newNode->_next = newNode;
        newNode->_prev = newNode;
        _deque = newNode;
    }
    else {
        cellule* frontNode = _deque->_next;
        newNode->_next = frontNode;
        newNode->_prev = _deque;
        _deque->_next = newNode;
        frontNode->_prev = newNode;
    }
}

// Add an element to the back
template<class TYPE>
inline void deque<TYPE>::push_back(const TYPE& element) {
    cellule* newNode = new cellule(element, nullptr, nullptr);

    if (empty()) {
        newNode->_next = newNode;
        newNode->_prev = newNode;
        _deque = newNode;
    }
    else {
        newNode->_next = _deque->_next;
        newNode->_prev = _deque;
        _deque->_next->_prev = newNode;
        _deque->_next = newNode;
        _deque = newNode; // Update back pointer
    }
}

// Assignment operator
template<class TYPE>
inline const deque<TYPE>& deque<TYPE>::operator=(const deque<TYPE>& other) {
    if (this != &other) {
        clear();
        if (!other.empty()) {
            cellule* current = other._deque->_next;
            do {
                push_back(current->_element);
                current = current->_next;
            } while (current != other._deque->_next);
        }
    }
    return *this;
}

// Access element at a specific index
template<class TYPE>
inline const TYPE& deque<TYPE>::at(int index) const {
    int dequeSize = size();
    if (index < 0 || index >= dequeSize)
        throw std::out_of_range("Index out of range");

    cellule* current = _deque->_next;
    for (int i = 0; i < index; ++i) {
        current = current->_next;
    }
    return current->_element;
}

// Overloaded [] operator for element access
template<class TYPE>
inline const TYPE& deque<TYPE>::operator[](int index) const {
    return at(index);
}
