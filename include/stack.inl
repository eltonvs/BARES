/*!
 *  @file stack.inl
 *  @brief Stack Implementations
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with Stack Class implementations
 */

#include "stack.hpp"

// Constructor
template <typename Object>
Stack<Object>::Stack(unsigned _sz) {
    m_stack = new Object[_sz];
    m_capacity = _sz;
}

// Destructor
template <typename Object>
Stack<Object>::~Stack() {
    delete[] m_stack;
}

template <typename Object>
bool Stack<Object>::push(const Object &_x) {
    if (isFull())
        if (!_double())
            return false;

    m_stack[m_top++] = _x;
    return true;
}

template <typename Object>
bool Stack<Object>::pop(Object &_returned) {
    if (isEmpty())
        return false;

    _returned = m_stack[--m_top];
    return true;
}

template <typename Object>
bool Stack<Object>::top(Object &_returned) const {
    if (isEmpty())
        return false;

    _returned = m_stack[m_top-1];
    return true;
}

template <typename Object>
unsigned Stack<Object>::size() const {
    return m_top;
}

template <typename Object>
bool Stack<Object>::isEmpty() const {
    return m_top == 0;
}

template <typename Object>
bool Stack<Object>::isFull() const {
    return m_top == m_capacity;
}

template <typename Object>
bool Stack<Object>::makeEmpty() {
    try {
        delete[] m_stack;
        m_stack = new Object;
    } catch (std::bad_alloc &e) {
        return false;
    }

    m_top      = 0;
    m_capacity = 1;
    return true;
}

// Double Size
template <typename Object>
bool Stack<Object>::_double() {
    Stack<Object> cpStack(m_capacity);
    Object aux;

    while (pop(aux))
        cpStack.push(aux);

    // Delete old Stack array to avoid memory leak
    delete[] m_stack;

    try {
        m_stack = new Object[m_capacity * 2];
    } catch (std::bad_alloc &e) {
        return false;
    }

    m_capacity *= 2;

    while (cpStack.pop(aux))
        push(aux);

    return true;
}
