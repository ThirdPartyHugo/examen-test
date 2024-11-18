template <class TYPE>
class stack
{
private:
	struct cellule
	{
		TYPE _element;			// élément ds la cellule
		cellule* _next; 		// pointeur vers prochaine cellule

		cellule(const TYPE& e, cellule* n)
		{
			_element = e;
			_next = n;
		}
	};
	cellule* _top;		// 1er élément de la pile
public:
	stack();			// constructeurr & destructeurr
	~stack();

	void push(const TYPE& e);
	TYPE pop();

	const TYPE& top() const;
	TYPE& top();
	int size() const;

	bool empty() const;
	void clear();

	const stack& operator=(const stack& s);
	bool operator==(const stack& s) const;
};

template<class TYPE>
inline stack<TYPE>::stack()
{
	_top = nullptr;
}

template<class TYPE>
inline stack<TYPE>::~stack()
{
	clear();
}

template<class TYPE>
inline void stack<TYPE>::push(const TYPE& e)
{
	_top = new cellule(e, _top);
}

template<class TYPE>
inline TYPE stack<TYPE>::pop()
{
	TYPE element = _top->_element;
	cellule* tempPtr = _top->_next;
	delete _top;
	_top = tempPtr;
	return element;
}

template<class TYPE>
inline const TYPE& stack<TYPE>::top() const
{
	return _top->_element;
}

template<class TYPE>
inline TYPE& stack<TYPE>::top()
{
	return _top->_element;
}

template<class TYPE>
inline int stack<TYPE>::size() const
{
	int size = 0;
	cellule* tempPtr = _top;
	while (tempPtr != nullptr)
	{
		size++;
		tempPtr = tempPtr->_next;
	}
	return size;
}

template<class TYPE>
inline bool stack<TYPE>::empty() const
{
	return (_top == nullptr);
}

template<class TYPE>
inline void stack<TYPE>::clear()
{
	while (!empty())
		pop();
}

template<class TYPE>
inline const stack<TYPE>& stack<TYPE>::operator=(const stack& s)
{
	if (this != &s) {
		clear();
		cellule* tempPtr1 = _top;
		cellule* tempPtr2 = s._top;

		if (tempPtr2 != nullptr)
		{
			_top = new cellule(tempPtr2->_element, nullptr);
			tempPtr1 = _top;
			tempPtr2 = tempPtr2->_next;

			while (tempPtr2 != nullptr)
			{
				tempPtr1->_next = new cellule(tempPtr2->_element, nullptr);
				tempPtr1 = tempPtr1->_next;
				tempPtr2 = tempPtr2->_next;
			}
		}
	}
	return *this;
}

template<class TYPE>
inline bool stack<TYPE>::operator==(const stack& s) const
{
	cellule* temp1 = _top;
	cellule* temp2 = s._top;

	while (temp1 != nullptr && temp2 != nullptr) {
		if (temp1->_element != temp2->_element)
			return false;
		temp1 = temp1->_next;
		temp2 = temp2->_next;
	}
	return (temp1 && temp2);
}