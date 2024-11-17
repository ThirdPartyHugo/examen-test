#include <fstream>


template <class TYPE>
class liste {
protected:
	struct cellule
	{
		TYPE _element;
		cellule* _next;
		cellule* _previous;
		cellule(const TYPE& e, cellule* n, cellule* p)
		{
			_element = e;
			_next = n;
			_previous = p;
		}
	};

	cellule* _premier;
	cellule* _dernier;
	cellule* _courant;
	liste(const liste& listObj); // Copieur d�sactiv�
public:
	liste(); // Constructeur
	~liste(); // Destructeur
	bool empty() const; // Retourne vrai si la liste est vide et faux
	// sinon
	void clear(); // Vide la liste
	void next(); // Positionne _courant sur la cellule suivante. Si
	// _courant est sur la derni�re cellule, il tombe �
	// nullptr et si _courant est d�j� � nullptr, il 
		// reste (aucune erreur g�n�r�e)
	void previous(); // Positionne _courant sur la cellule pr�c�dente.
	// Si _courant est � nullptr, il se met � pointer
	// la derni�re cellule de la liste et s�il est
	// sur la premi�re cellule de la liste, il y reste
	// (aucune erreur g�n�r�e)
	void begin(); // Positionne _courant sur la premi�re cellule
	void end(); // Positionne _courant en fin de liste (nullptr)
	bool isBegin() const; // Retourne vrai si _courant est au d�but de
	// la liste ou faux sinon
	bool isEnd() const; // Retourne vrai si _courant est � la fin de la
	// liste (nullptr) ou faux sinon
	TYPE& value() const; // Retourne la valeur pr�sente dans la cellule
	// point�e par _courant
	int size() const; // Retourne le nombre de cellules de la liste
	void insert(const TYPE& element); // Ins�re une nouvelle cellule avec
	// l��l�ment re�u juste avant la
	// position de _courant. Ce dernier
	// reste au m�me endroit qu�avant
	// l'insertion
	void erase(); // D�salloue la cellule cibl�e par _courant. _courant est
	// ensuite positionn� sur la cellule venant juste apr�s celle
	// qui vient d��tre d�sallou�e. Si la derni�re cellule vient
	// d��tre d�sallou�e, _courant tombe � nullptr
	void print(std::ostream& out); // Affiche le contenu de la liste
	const liste& operator=(const liste& l); // Affectateur
};



template<class TYPE>
inline liste<TYPE>::liste()
{

	_premier = nullptr;
	_dernier = nullptr;
	_courant = _premier;
}

template<class TYPE>
inline liste<TYPE>::~liste()
{
	clear();
}

template<class TYPE>
inline bool liste<TYPE>::empty() const
{
	if (_premier == nullptr) {
		return true;
	}
	return false;
}

template<class TYPE>
inline void liste<TYPE>::clear()
{
	while (_premier != nullptr) {
		_courant = _premier;
		_premier = _premier->_next;
		delete _courant;
	}
	_dernier = nullptr;
	_courant = nullptr;
}

template<class TYPE>
inline void liste<TYPE>::next()
{
	if (_courant == nullptr) {

	}
	else {
		_courant = _courant->_next;
		
	}
}

template<class TYPE>
inline void liste<TYPE>::previous()
{
	if (_courant == nullptr) {
		_courant = _dernier;
	}
	else if (_courant == _premier) {
		
	}
	else {
		_courant = _courant->_previous;
	}
		
	
}

template<class TYPE>
inline void liste<TYPE>::begin()
{
	_courant = _premier;
}

template<class TYPE>
inline void liste<TYPE>::end()
{
	_courant = nullptr;
}

template<class TYPE>
inline bool liste<TYPE>::isBegin() const
{
	if (_courant == _premier || _premier == nullptr) {
		return true;
	}
	return false;
}

template<class TYPE>
inline bool liste<TYPE>::isEnd() const
{
	if (_courant ==  nullptr  ) {
		return true;
	}
	return false;
}

template<class TYPE>
inline TYPE& liste<TYPE>::value() const
{
	assert("_courant != nullptr");
	std::cout << _courant->_element << std::endl;
	return _courant->_element;
}

template<class TYPE>
inline int liste<TYPE>::size() const
{
	int index = 0;
	cellule* temp = _premier;
	while (temp != nullptr) {
		index++;
		temp = temp->_next;
	}
	return index;
}

template<class TYPE>
inline void liste<TYPE>::insert(const TYPE& element)
{
	// Create a new cell containing the element
	cellule* newCell = new cellule(element, nullptr, nullptr);

	if (_courant == nullptr) {
		// If _courant is nullptr, insert at the end
		newCell->_previous = _dernier;
		if (_dernier != nullptr)
			_dernier->_next = newCell;
		else
			_premier = newCell; // The list was empty
		_dernier = newCell;
	}
	else {
		// Insert before _courant
		newCell->_next = _courant;
		newCell->_previous = _courant->_previous;
		if (_courant->_previous != nullptr)
			_courant->_previous->_next = newCell;
		else
			_premier = newCell; // Inserting at the beginning
		_courant->_previous = newCell;
	}
}

template<class TYPE>
inline void liste<TYPE>::erase()
{
	if (_courant == nullptr) {
		// Cannot erase a null pointer
		return;
	}
	cellule* temp = _courant;

	// Update links
	if (_courant->_previous != nullptr) {
		_courant->_previous->_next = _courant->_next;
	}
	else {
		// _courant is the first node
		_premier = _courant->_next;
	}

	if (_courant->_next != nullptr) {
		_courant->_next->_previous = _courant->_previous;
	}
	else {
		// _courant is the last node
		_dernier = _courant->_previous;
	}

	// Move _courant to next node
	_courant = _courant->_next;

	// Delete the node
	delete temp;

	// If the list is empty, set pointers to nullptr
	if (_premier == nullptr) {
		_dernier = nullptr;
		_courant = nullptr;
	}

}

template<class TYPE>
inline void liste<TYPE>::print(std::ostream& out)
{
	cellule* temp = _premier;
	while (temp != nullptr) {
		out << temp->_element << " ";
		temp = temp->_next;
	}
	out << std::endl;
}

