#include <cassert> // For exception handling

template <class TYPE>
class stack
{
private:
    struct cellule
    {
        TYPE    element;   // Element in the cell
        cellule* next;     // Pointer to the next cell

        cellule(const TYPE& e, cellule* n)
        {
            element = e;
            next = n;
        }
    };
    cellule* _top;     // Top element of the stack
public:
    stack();            // Constructor
    ~stack();           // Destructor
    void push(const TYPE& e);     // Adds a new top element
    void pop();                     // Removes the top element
    const TYPE& top() const;        // Returns the top element (read-only)
    TYPE& top();                    // Returns the top element (modifiable)
    int size() const;               // Returns the number of elements
    bool empty() const;             // Checks if the stack is empty
    void clear();                   // Clears the stack
    const stack& operator=(const stack& s); // Assignment operator
    bool operator==(const stack& s) const;  // Compares two stacks
};

template<class TYPE>
inline stack<TYPE>::stack()
{
    _top = nullptr; // Initialize top to nullptr
}

template<class TYPE>
inline stack<TYPE>::~stack()
{
    clear(); // Delete all nodes
}

template<class TYPE>
inline void stack<TYPE>::push(const TYPE& e)
{
    _top = new cellule(e, _top); // Create a new node at the top
}

template<class TYPE>
inline void stack<TYPE>::pop()
{
    assert("_top != nullptr");
    
    
        cellule* temp = _top;
        _top = _top->next;
        delete temp;
    
    
}

template<class TYPE>
inline const TYPE& stack<TYPE>::top() const
{
    if (_top != nullptr)
        return _top->element;
    else
        throw std::out_of_range("Stack is empty: cannot access top element");
}

template<class TYPE>
inline TYPE& stack<TYPE>::top()
{
    if (_top != nullptr)
        return _top->element;
    else
        throw std::out_of_range("Stack is empty: cannot access top element");
}

template<class TYPE>
inline int stack<TYPE>::size() const
{
    int count = 0;
    cellule* temp = _top;
    while (temp != nullptr)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

template<class TYPE>
inline bool stack<TYPE>::empty() const
{
    return _top == nullptr;
}

template<class TYPE>
inline void stack<TYPE>::clear()
{
    while (_top != nullptr)
    {
        cellule* temp = _top;
        _top = _top->next;
        delete temp;
    }
}

template<class TYPE>
inline const stack<TYPE>& stack<TYPE>::operator=(const stack& s)
{
    if (this != &s)
    {
        clear(); // Clear current stack

        if (s._top != nullptr)
        {
            // Copy the first node
            _top = new cellule(s._top->element, nullptr);

            cellule* curr_new = _top;
            cellule* curr_s = s._top->next;

            // Copy the rest of the nodes
            while (curr_s != nullptr)
            {
                curr_new->next = new cellule(curr_s->element, nullptr);
                curr_new = curr_new->next;
                curr_s = curr_s->next;
            }
        }
    }
    return *this;
}

template<class TYPE>
inline bool stack<TYPE>::operator==(const stack& s) const
{
    cellule* curr1 = _top;
    cellule* curr2 = s._top;

    while (curr1 != nullptr && curr2 != nullptr)
    {
        if (!(curr1->element == curr2->element))
            return false;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    return curr1 == nullptr && curr2 == nullptr;
}
