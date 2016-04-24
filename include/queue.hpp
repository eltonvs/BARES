/*!
 *  @file queue.hpp
 *  @brief Queue Class Header
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with the Queue Class header
 */

#ifndef _queue_hpp_
#define _queue_hpp_

/**
 * @brief Queue Class
 *
 * The Queue implementation.
 */
template <typename Object>
class Queue {
 public:
    /**
     * @brief Queue Constructor
     * @param _sz Receives the initial Queue size
     *
     * Creates a Stack with _sz size (default = 1)
     */
    explicit Queue(const unsigned _sz = 1);

    /**
     * @brief Queue Destructor
     *
     * Delete allocated data and set all to 0
     */
    ~Queue();

    /**
     * @brief Insert an element on Queue
     * @param _x Receives an element to enqueue
     * @return True if the element was successfully enqueued, False otherwise
     */
    bool enqueue(const Object &_x);

    /**
     * @brief Remove an element from Queue
     * @param _return Keep the removed element
     * @return True if the element was successfully removed, False otherwise
     */
    bool dequeue(Object &_return);

    /**
     * @brief Gets the element on front of Queue
     * @param _return Keep the front element
     * @return True if the element was successfully accessed, False otherwise
     */
    bool front(Object &_return) const;

    /**
     * @brief Get the Queue size
     * @return A unsigned int with the Queue size
     */
    unsigned size() const;

    /**
     * @brief Verify if the Queue is Empty
     * @return True if the Queue is Empty, False if not
     */
    bool isEmpty() const;

    /**
     * @brief Verify if the Queue is Full
     * @return True if the Queue is Full, False if not
     */
    bool isFull() const;

    /**
     * @brief Make the Queue empty
     * @return True if the Queue was successfully empty, False if not
     */
    bool makeEmpty();

    /**
     * @brief Overload the << operator to Queues
     * @param _os The std::ostream
     * @param _queue The Queue to be showed
     * @return A std::ostream with the Queue content
     */
    inline friend
    std::ostream &operator<<(std::ostream &_os, const Queue &_queue) {
        _os << "[ ";
        for (auto i(0u); i < _queue.size(); i++)
            _os << _queue.m_queue[(_queue.m_f + i) % _queue.m_capacity] << " ";
        _os << "]";

        return _os;
    }

 private:
    /**
     * @brief Double the Stack capacity
     * @return True if the Stack successfully grew, False otherwise
     */
    bool _double();

    int m_f         = -1;       //!< The position of the front of Queue
    int m_r         = -1;       //!< The position of the rear of the Queue
    int m_capacity  = 0;        //!< The Queue capacity
    Object *m_queue = nullptr;  //!< A pointer to the first element on memory
};

#include "queue.inl"

#endif
