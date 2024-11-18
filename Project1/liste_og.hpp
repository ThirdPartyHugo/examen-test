#pragma once
#include <cassert>

template <typename T>
class List;

// Classe d'une cellule. La liste est composée de plusieurs de ces cellules
template <typename T>
class Cellule {
private:
    T _element; // Contenu d'une cellule de la liste
    Cellule<T>* _next; // Pointeur vers la cellule suivante de la liste
    Cellule<T>* _prev; // Pointeur vers la cellule précédente de la liste

    // Constructeur d'une cellule (méthode appelée à chaque fois qu'on fait un "new Cellule")
    Cellule(const T& element, Cellule<T>* next = nullptr, Cellule<T>* prev = nullptr) {
        _element = element;
        _next = next;
        _prev = prev;
    }

    friend class List<T>; /* La classe "List" a accès à la représentation de la cellule bien que la classe
                             "Cellule" ait été déclarée à l'extérieur de la classe "List". */
};

template <typename T>
class List {
private:
    Cellule<T>* _first; // Pointe sur la première cellule de la liste

public:
    // Classe d'un itérateur d'une liste (un itérateur doit être associé à une liste pour pointer une de ses cellules).
    class Iterator {
    private:
        Cellule<T>* _current; // Adresse de la cellule sur laquelle est présentement positionné l'itérateur
        const List<T>* _list; // Adresse de la liste concernée par l'itérateur

        friend class List<T>; // La classe "List" a accès à la représentation de l'itérateur

    public:
        Iterator(); // Constructeur qui initialise "_current" et "_list" à "nullptr".
        ~Iterator(); // Destructeur qui remet "_current" et "_list" à "nullptr".

        const Iterator& operator=(const Iterator&); // Pour assigner la valeur d'un itérateur à un autre
        bool operator==(const Iterator&) const; // Pour comparer deux itérateurs (ils traitent de la même liste à la même position)
        bool operator!=(const Iterator&) const;
        Iterator operator++(int); // Pour déplacer un itérateur à la cellule suivante (it++)
        const Iterator& operator++(); // Pour atteindre la cellule suivante sans modifier la position courante de l'itérateur (++it)
        Iterator operator--(int); // Pour déplacer un itérateur à la cellule précédente (it--)
        const Iterator& operator--(); // Pour atteindre la cellule précédente sans modifier la position courante de l'itérateur (--it)
        T& operator*(); // Pour accéder à l'élément pointé par l'itérateur (it*)
        const T& operator*() const; // Pour accéder à l'élément pointé par l'itérateur (it*) sans pouvoir le modifier
    };

    List(); // Constructeur qui initialise "_first" à "nullptr".
    List(const List<T>&); // Copieur (pour le désactiver, il faut le placer dans la section "private")
    ~List(); // Destructeur qui supprime toutes les cellules de la liste

    void clear(); // Méthode qui supprime toutes les cellules de la liste
    bool empty() const; // Méthode qui vérifie si la liste est vide (retourne true) ou non (retourne false)

    Iterator begin() const; // Méthode qui retourne un itérateur pointant sur la première cellule
    Iterator end() const; // Méthode qui retourne un itérateur ayant pour adresse "nullptr"

    Iterator insert(Iterator, const T&); // Méthode qui crée une nouvelle cellule juste avant la position de l'itérateur.
    Iterator erase(Iterator); // Méthode qui supprime la cellule occupant la position pointée par l'itérateur.
    Iterator erase(Iterator, Iterator); /* Méthode qui supprime toutes les cellules se retrouvant inclusivement entre le
                                           premier itérateur et le second itérateur passés en paramètres d'entrée. */
    T& operator[](Iterator); /* Cette surcharge d'opérateur [] n'est pas présente dans la librairie STL. Elle permet
                                d'accéder à l'élément contenu dans la cellule qui occupe l'index spécifié en paramètre
                                d'entrée. */
    const T& operator[](Iterator) const;

    Iterator operator()(const T&) const; /* Cette méthode cherche dans la liste l'occurrence de l'élément passé en paramètre
                                            d'entrée. Si cet élément est inexistant, un itérateur "nullptr" est retourné. */
    Iterator operator()(const T&, Iterator) const;

    const List<T>& operator=(const List<T>&); // Surcharge de l'opérateur = pour copier le contenu d'une liste vers une autre.
};

/********************************************************/
/* CODEZ CI-DESSOUS LES MÉTHODES DE LA CLASSE ITERATOR. */
/********************************************************/

template<typename T>
inline List<T>::Iterator::Iterator()
{
    _list = _current = nullptr;
}

template<typename T>
inline List<T>::Iterator::~Iterator()
{
    _list = _current = nullptr;
}

template<typename T>
inline const typename List<T>::Iterator& List<T>::Iterator::operator=(const List<T>::Iterator& autreIt)
{
    _current = autreIt._current;
    _list = autreIt._list;

    return *this;
}

template<typename T>
inline bool List<T>::Iterator::operator==(const Iterator& autreIt) const
{
    assert(_list == autreIt._list);
    assert(_list != nullptr);

    return _current == autreIt._current;
}

template<typename T>
inline bool List<T>::Iterator::operator!=(const Iterator& autreIt) const
{
    assert(_list == autreIt._list);
    assert(_list != nullptr);

    return _current != autreIt._current;
}

template<typename T>
inline typename List<T>::Iterator List<T>::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
inline const typename List<T>::Iterator& List<T>::Iterator::operator++()
{
    assert(_current != nullptr);
    _current = _current->_next;
    return *this;
}

template<typename T>
inline typename List<T>::Iterator List<T>::Iterator::operator--(int)
{
    Iterator temp = *this;
    --(*this);
    return temp;
}

template<typename T>
inline const typename List<T>::Iterator& List<T>::Iterator::operator--()
{
    assert(_current != nullptr);
    _current = _current->_prev;
    return *this;
}

template<typename T>
inline T& List<T>::Iterator::operator*()
{
    assert(_current != nullptr && _list != nullptr);
    assert(_list->_first != nullptr);
    return _current->_element;
}

template<typename T>
inline const T& List<T>::Iterator::operator*() const
{
    assert(_current != nullptr && _list != nullptr);
    assert(_list->_first != nullptr);
    return _current->_element;
}

/****************************************************/
/* CODEZ CI-DESSOUS LES MÉTHODES DE LA CLASSE LIST. */
/****************************************************/

template<typename T>
inline List<T>::List()
{
    _first = nullptr;
}

template<typename T>
inline List<T>::List(const List<T>& autreListe)
{
    _first = nullptr;
    *this = autreListe;
}

template<typename T>
inline List<T>::~List()
{
    clear();
}

template<typename T>
inline void List<T>::clear()
{
    erase(begin(), end());
}

template<typename T>
inline bool List<T>::empty() const
{
    return _first == nullptr;
}

template<typename T>
inline typename List<T>::Iterator List<T>::begin() const
{
    Iterator it;
    it._list = this;
    it._current = _first;
    return it;
}

template<typename T>
inline typename List<T>::Iterator List<T>::end() const
{
    Iterator it;
    it._list = this;
    it._current = nullptr;
    return it;
}

template<typename T>
inline typename List<T>::Iterator List<T>::insert(Iterator it, const T& element)
{
    assert(it._list == this);

    if (_first == nullptr) // On insère dans une liste initialement vide (il n'y a pas de cellules)
    {
        _first = new Cellule<T>(element, nullptr, nullptr);
        _first->_prev = _first;
        it._current = _first;
    }
    else if (it._current == _first) // On insère la cellule au tout début de la liste
    {
        _first = new Cellule<T>(element, _first, _first->_prev);
        _first->_next->_prev = _first;
        it._current = _first;
    }
    else if (it._current == nullptr) // On insère à la toute fin de la liste
    {
        it._current = new Cellule<T>(element, nullptr, _first->_prev);
        _first->_prev->_next = it._current;
        _first->_prev = it._current;
    }
    else // On insère une cellule entre deux autres cellules (ni au début, ni à la fin)
    {
        it._current = new Cellule<T>(element, it._current, it._current->_prev);
        it._current->_prev->_next = it._current;
        it._current->_next->_prev = it._current;
    }

    return it;
}

template<typename T>
inline typename List<T>::Iterator List<T>::erase(Iterator it)
{
    assert(it._list == this);
    assert(it._list != nullptr);
    assert(_first != nullptr);

    Cellule<T>* tempCell = it._current;

    if (_first == _first->_prev) // Si on supprime la seule cellule de la liste
    {
        _first = it._current = nullptr;
    }
    else if (it._current == _first) // Si on supprime la première cellule de la liste
    {
        _first = _first->_next;
        _first->_prev = tempCell->_prev;
        it._current = _first;
    }
    else if (it._current == _first->_prev) // Si on supprime la dernière cellule de la liste
    {
        it._current->_prev->_next = nullptr;
        _first->_prev = it._current->_prev;
        it._current = nullptr;
    }
    else // Si on supprime une cellule se retrouvant entre deux cellules de la liste
    {
        it._current->_next->_prev = it._current->_prev;
        it._current->_prev->_next = it._current->_next;
        it._current = it._current->_next;
    }

    delete tempCell;

    return it;
}

template<typename T>
inline typename List<T>::Iterator List<T>::erase(Iterator it1, Iterator it2)
{
    assert(it1._list == this && it2._list == this);
    assert(it1._list != nullptr && it2._list != nullptr);

    while (it1 != it2) {
        it1 = erase(it1);
    }

    return it2;
}

template<typename T>
inline T& List<T>::operator[](Iterator it)
{
    return *it;
}

template<typename T>
inline const T& List<T>::operator[](Iterator it) const
{
    return *it;
}

template<typename T>
inline typename List<T>::Iterator List<T>::operator()(const T& li) const
{
    Iterator it = begin();
    while (it != end()) {
        if (*it == li) {
            return it;
        }
        ++it;
    }
    return end();
}

template<typename T>
inline typename List<T>::Iterator List<T>::operator()(const T& li, Iterator it) const
{
    while (it != end()) {
        if (*it == li) {
            return it;
        }
        ++it;
    }
    return end();
}

template<typename T>
inline const List<T>& List<T>::operator=(const List<T>& autreLi)
{
    if (this == &autreLi)
        return *this;

    clear();

    for (Iterator it = autreLi.begin(); it != autreLi.end(); ++it) {
        insert(end(), *it);
    }

    return *this;
}