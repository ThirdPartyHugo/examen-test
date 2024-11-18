
template <class TYPE>
class file {
private:
	TYPE* _tab; // Tableau de la file
	int _tete; // Index de la tête de la file
	int _queue; // Index de la queue de la file
	file(const file&); // Copieur désactivé
public:
	file(int taille); // Constructeur de file avec une taille spécifiée
	~file(); // Destructeur de file
	void enfiler(const TYPE & element); // Ajoute l’élément à la queue
	// de la file
	TYPE defiler(); // Enlève l’élément à la tête de la file et le
	// retourne
	const TYPE& tete() const; // Retourne l’élément à la tête
	bool estVide() const; // Vérifie si la file est vide ou non
	void vider(); // Vide la file (désalloue le tableau complet)
	//const file& operator=(const file&); // Affectateur de files
};

template<class TYPE>
inline file<TYPE>::file(int taille)
{
	_tab = new TYPE[taille];
	_tete = 0;
	_queue = taille;
}
template<class TYPE>
inline file<TYPE>::~file()
{
    delete[] _tab;
}
template<class TYPE>
inline void file<TYPE>::enfiler(const TYPE& element)
{

    int newCapacity = _queue + 1;

    TYPE* newTab = new TYPE[newCapacity];

    for (int i = 0; i < _queue; ++i)
    {
        newTab[i] = _tab[i];
        
        std::cout << _tab[i] << std::endl;
    }

    newTab[_queue] = element;

    delete[] _tab;

    _tab = newTab;

    _queue++;
    
}



template<class TYPE>
inline TYPE file<TYPE>::defiler()
{
    if (estVide())
    {
       
    }

    TYPE element = this->tete();
    _tete = _tete + 1;
    return element;
}

template<class TYPE>
inline const TYPE& file<TYPE>::tete() const
{
    if (estVide())
    {
        
    }
    return _tab[_tete];
}

template<class TYPE>
inline bool file<TYPE>::estVide() const
{
    return _tete == _queue;
}

template<class TYPE>
inline void file<TYPE>::vider()
{
    delete[] _tab;
    _tab = new TYPE[_queue];
    _tete = 0;
    _queue = 0;
}

