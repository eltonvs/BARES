/*!
 *  @file headers.hpp
 *  @brief Class Headers
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with all Class Headers and prototypes
 */

#ifndef _stack_hpp_
#define _stack_hpp_

template <typename Object>
class Stack {
 public:
    // Constructor
    Stack(unsigned _sz = 1);
    // Destructor
    ~Stack();

    // Members
    bool push(const Object &_x);
    bool pop(Object &_return);
    bool top(Object &_return) const;

    // Helpers
    bool isEmpty() const;
    bool isFull() const;
    bool makeEmpty();

 protected:
    bool _double();
    int m_top       = 0;
    int m_capacity  = 0;
    Object *m_stack = nullptr;
};

#include "stack.inl"

#endif
