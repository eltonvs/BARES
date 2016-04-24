/*!
 *  @file stack.hpp
 *  @brief Class Headers
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with all Class Headers and prototypes
 */

#ifndef _stack_hpp_
#define _stack_hpp_

/**
 * @brief Stack Class
 *
 * The Stack implementation.
 */
template <typename Object>
class Stack {
 public:
    /**
     * @brief Stack Constructor
     * @param _sz Receives the initial Stack size
     *
     * Creates a Stack with _sz size (default = 1)
     */
    explicit Stack(const unsigned _sz = 1);

    /**
     * @brief Stack Destructor
     *
     * Delete allocated data and set all to 0
     */
    ~Stack();

    /**
     * @brief Insert an element on Stack
     * @param _x Receives an element to push on Stack
     * @return True if the element was successfully added, False otherwise
     */
    bool push(const Object &_x);

    /**
     * @brief Remove an element from Stack
     * @param _return Keep the removed element
     * @return True if the element was successfully removed, False otherwise
     */
    bool pop(Object &_return);

    /**
     * @brief Gets the element on top of Stack
     * @param _return Keep the top element
     * @return True if the element was successfully accessed, False otherwise
     */
    bool top(Object &_return) const;

    /**
     * @brief Verify if the Stack is Empty
     * @return True if the Stack is Empty, False if not
     */
    bool isEmpty() const;

    /**
     * @brief Verify if the Stack is Full
     * @return True if the Stack is Full, False if not
     */
    bool isFull() const;

    /**
     * @brief Make the Stack empty
     * @return True if the Stack was successfully empty, False if not
     */
    bool makeEmpty();

    /**
     * @brief Overload the << operator to Stacks
     * @param _os The std::ostream
     * @param _stack The Stack to be showed
     * @return A std::ostream with the Stack content
     */
    inline friend
    std::ostream &operator<<(std::ostream &_os, const Stack &_stack) {
        _os << "[ ";
        for (auto i(0u); i < _stack.m_top; i++)
            _os << _stack.m_stack[i] << " ";
        _os << "]";

        return _os;
    }

 protected:
    /**
     * @brief Double the Stack capacity
     * @return True if the Stack successfully grew, False otherwise
     */
    bool _double();

    int m_top       = 0;        //!< The number of elements on Stack
    int m_capacity  = 0;        //!< The Stack capacity
    Object *m_stack = nullptr;  //!< A pointer to the first element on memory
};

#include "stack.inl"

#endif
