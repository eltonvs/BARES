/*!
 *  @file term.hpp
 *  @brief Term Class Header
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with the Term Class header
 */

#ifndef _term_hpp_
#define _term_hpp_

#include <string>
#include "queue.hpp"

/**
 * @brief Term Class
 *
 * The Term implementation.
 */
class Term {
 public:
    /**
     * @brief Term Constructor
     * @param _term Receives the Term content
     * @param _col Receives the Term collumn
     *
     * Creates a Term
     */
    explicit Term(std::string _term = "", int _col = -1);

    /**
     * @brief Term Destructor
     *
     * Destroy a Term
     */
    ~Term();

 private:
    std::string m_term = "";  //<! The term value
    int m_col = -1;           //<! The term column on expression
};

#include "term.inl"

#endif
