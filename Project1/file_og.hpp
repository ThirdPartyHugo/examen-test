#pragma once

template <class TYPE>
class queue {
private:
	struct cellule { // Structure d'une cellule. La file est compos�e de plusieurs de ces cellules
		TYPE _element; // Donn�e enregistr�e dans une des cellules de la file
		cellule* _next; // Pointeur vers la prochaine cellule de la file

		// Constructeur d'une cellule (m�thode appel�e � chaque fois qu'on fait un "new Cellule")
		Cellule(const TYPE& element, cellule* next) {
			_element = element;
			_next = next;
		}
	};

	cellule* _queue; // Pointe sur la derni�re cellule dont le "next" pointe sur la premi�re

public:
	queue(); // Constructeur qui initialise "_queue" � "nullptr"
	~queue(); // Destructeur qui supprime toutes les cellules de la file

	void clear(); // M�thode qui supprime toutes les cellules de la file
	bool empty() const; // M�thode qui v�rifie si la file est vide (retourne true) ou non (retourne false)
	int size() const; // M�thode qui retourne le nombre de cellules que contient la file

	const TYPE& front() const; // M�thode qui retourne l'�l�ment contenu dans la premi�re cellule de la file
	TYPE pop(); // M�thode qui supprime la premi�re cellule de la file et retourne son �l�ment par valeur
	void push(const TYPE&); // M�thode qui ajoute une nouvelle cellule � la fin de la file

	const queue<TYPE>& operator=(const queue<TYPE>&); // Surcharge de l'op�rateur = pour copier le contenu
	// d'une file vers une autre.
};

// CODEZ LES M�THODES DE VOTRE FILE ICI.

template<class TYPE>
inline queue<TYPE>::queue()
{
	_queue = nullptr;
}

template<class TYPE>
inline queue<TYPE>::~queue()
{
	clear();
}

template<class TYPE>
inline void queue<TYPE>::clear()
{
	while (!empty())
		pop();
}

template<class TYPE>
inline bool queue<TYPE>::empty() const
{
	return (_queue == nullptr);
}

template<class TYPE>
inline int queue<TYPE>::size() const
{
	int count = 0;

	if (_queue !nullptr)
	{
		cellule* tempPtr = _queue->_next;
		do
		{
			count++;
			tempPtr = tempPtr->_next;
		} while (tempPtr != _queue->_next)
	}
	return count;
}

template<class TYPE>
inline const TYPE& queue<TYPE>::front() const
{
	assert(_queue != nullptr);

	return _queue->_next->_element;
}

template<class TYPE>
inline TYPE queue<TYPE>::pop()
{
	assert(_queue != nullptr);

	TYPE temp = _queue->_next->_element;

	if (_queue == _queue->_next)
	{
		delete _queue;
		_queue = nullptr;
	}
	else
	{
		cellule* tempPtr = _queue->_next->_next;
		delete _queue->_next;
		_queue->_next = tempPtr;
	}
	return temp;
}

template<class TYPE>
inline void queue<TYPE>::push(const TYPE& e)
{
	if (_queue == nullptr)
	{
		_queue = new cellule(e, _queue);
		_queue->_next = _queue;
	}
	else
	{
		_queue->_next = new cellule(e, _queue->_next);
		_queue->_next;
	}
}

template<class TYPE>
inline const queue<TYPE>& queue<TYPE>::operator=(const queue<TYPE>& q)
{
	if (this == &q)
		return *this;

	clear();
	if (q._queue != nullptr)
	{
		cellule* tempPtr = q._queue->_next;
		do
		{
			push(tempPtr->_element);
			tempPtr = tempPtr->_next;
		} while (tempPtr != q._queue->_next);
	}
	return *this;
}