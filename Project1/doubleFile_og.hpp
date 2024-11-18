#pragma once

#include <cassert>

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

/************************************************/
/* CODEZ LES MÉTHODES DE VOTRE DOUBLE-FILE ICI. */
/************************************************/

template<class TYPE>
inline deque<TYPE>::deque()
{
	_deque = nullptr;
}

template<class TYPE>
inline deque<TYPE>::deque(const deque<TYPE>& element)
{
	_deque = nullptr;
	cellule* tempPtr = element._deque;
	while (tempPtr)
	{
		push_back(tempPtr->_element);
		tempPtr = tempPtr->_next;
	}
}

template<class TYPE>
inline deque<TYPE>::~deque()
{
	clear();
}

template<class TYPE>
inline bool deque<TYPE>::empty() const
{
	return _deque == nullptr;
}

template<class TYPE>
inline int deque<TYPE>::size() const
{
	int count = 0;

	if (_deque != nullptr)
	{
		cellule* tempPtr = _deque->_next;
		do
		{
			count++;
			tempPtr = tempPtr->_next;
		} while (tempPtr != _deque->_next);
	}
	return count;
}

template<class TYPE>
inline void deque<TYPE>::clear()
{
	while (!empty())
		pop_front();
}

template<class TYPE>
inline const TYPE& deque<TYPE>::front() const
{
	assert(!empty());
	return _deque->_next->_element;
}

template<class TYPE>
inline const TYPE& deque<TYPE>::back() const
{
	assert(!empty());
	return _deque->_element;
}

template<class TYPE>
inline TYPE deque<TYPE>::pop_front()
{
	assert(!empty());

	TYPE tempVal = _deque->_next->_element;

	if (_deque == _deque->_next)
	{
		delete _deque;
		_deque = nullptr;
	}
	else
	{
		cellule* tempPtr = _deque->_next->_next;
		tempPtr->_prev = _deque;
		delete _deque->_next;
		_deque->_next = tempPtr;
	}

	return tempVal;
}

template<class TYPE>
inline TYPE deque<TYPE>::pop_back()
{
	assert(!empty());

	TYPE tempVal = _deque->_element;

	if (_deque == _deque->_prev)
	{
		delete _deque;
		_deque = nullptr;
	}
	else
	{
		cellule* tempPtr = _deque->_prev;
		_deque->_next->_prev = tempPtr;
		tempPtr->_next = _deque->_next;
		delete _deque;
		_deque = tempPtr;
	}
	return tempVal;
}

template<class TYPE>
inline void deque<TYPE>::push_front(const TYPE& element)
{
	if (empty())
	{
		_deque = new cellule(element, nullptr, nullptr);
		_deque->_next = _deque;
		_deque->_prev = _deque;
	}
	else
	{
		_deque->_next = _deque->_next->_prev = new cellule(element, _deque->_next, _deque);
	}
}

template<class TYPE>
inline void deque<TYPE>::push_back(const TYPE& element)
{
	if (empty())
	{
		_deque = new cellule(element, nullptr, nullptr);
		_deque->_next = _deque;
		_deque->_prev = _deque;
	}
	else
	{
		_deque = _deque->_next = _deque->_next->_prev = new cellule(element, _deque->_next, _deque);
	}
}

template<class TYPE>
inline const deque<TYPE>& deque<TYPE>::operator=(const deque<TYPE>& d)
{
	if (this == &d)
		return *this;

	clear();

	if (d._deque != nullptr)
	{
		cellule* tempPtr = d._deque->_next;
		do
		{
			push_back(tempPtr->_element);
			tempPtr = tempPtr->_next;
		} while (tempPtr != d._deque->_next);
	}

	return *this;
}

template<class TYPE>
inline const TYPE& deque<TYPE>::at(int index) const
{
	int taille = size();

	assert(index >= 0 && index < taille);

	if (index == taille - 1)
	{
		return back();
	}

	int pos = 0;

	cellule* tempPtr = _deque->_next;

	while (pos < index)
	{
		tempPtr = tempPtr->_next;
		pos++;
	}

	return tempPtr->_element;
}

template<class TYPE>
inline const TYPE& deque<TYPE>::operator[](int index) const
{
	return at(index);
}