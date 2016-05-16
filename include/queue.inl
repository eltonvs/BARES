/*!
 *  @file queue.inl
 *  @brief Queue Implementations
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with Queue Class implementations
 */

#include "stack.hpp"

// Constructor
template <typename Object>
Queue<Object>::Queue(const unsigned _sz) {
    m_capacity = _sz;
    m_queue = new Object[_sz];
}

// Destructor
template <typename Object>
Queue<Object>::~Queue() {
    delete[] m_queue;
}

template <typename Object>
bool Queue<Object>::enqueue(const Object &_a) {
    if (m_f == -1) {
        m_f = m_r = 0,
        m_queue[0] = _a;
        return true;
    }

    if (isFull())
        if (!_double())
            return false;

    auto final_b = (m_r + 1)%m_capacity;
    m_queue[final_b] = _a, m_r = final_b;

    return true;
}

template <typename Object>
bool Queue<Object>::dequeue(Object &_a) {
    if (isEmpty())
        return false;

    // Copy the front element
    if(!front(_a))
        return false;

    if (m_r == m_f)
        m_r = m_f = -1;
    else
        m_f = (m_f + 1)%m_capacity;

    return true;
}

template <typename Object>
bool Queue<Object>::front(Object &_a) const {
    if (isEmpty())
        return false;

    // Copy the front element
    _a = m_queue[m_f];
    return true;
}

template <typename Object>
unsigned Queue<Object>::size() const {
    if (isEmpty())
        return 0;
    if (m_f > m_r)
        return m_capacity - m_f + m_r + 1;
    return m_r - m_f + 1;
}

template <typename Object>
bool Queue<Object>::isEmpty() const {
    return m_f == -1;
}

template <typename Object>
bool Queue<Object>::isFull() const {
    return (m_r + 1)%m_capacity == m_f;
}

template <typename Object>
bool Queue<Object>::makeEmpty() {
    try {
        delete[] m_queue;
        m_queue = new Object;
    } catch (std::bad_alloc &e) {
        return false;
    }

    m_f = m_r = -1;
    m_capacity = 1;
    return true;
}

// Double Size
template <typename Object>
bool Queue<Object>::_double() {
    Queue<Object> copy(m_capacity);
    Object aux;
    while (dequeue(aux))
        if (!copy.enqueue(aux))
            return false;

    // Delete old Queue array to avoid memory leak
    delete[] m_queue;

    try {
        m_queue = new Object[m_capacity * 2];
    } catch (std::bad_alloc &e) {
        return false;
    }

    m_capacity *= 2;

    while (copy.dequeue(aux))
        if (!enqueue(aux))
            return false;

    return true;
}
