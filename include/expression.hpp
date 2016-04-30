/*!
 *  @file expression.hpp
 *  @brief Expression Class Header
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with the Expression Class header
 */

#ifndef _expression_hpp_
#define _expression_hpp_

#include <string>
#include "queue.hpp"
#include "term.hpp"

/**
 * @brief Expression Class
 *
 * The Expression implementation.
 */
class Expression {
 public:
    /**
     * @brief Expression Constructor
     * @param _expr Receives the initial Expression content
     *
     * Creates a Expression with a string (default = "")
     */
    explicit Expression(std::string _expr = "");

    /**
     * @brief Expression Destructor
     *
     * Delete expression and empty all Queues
     */
    ~Expression();

    /**
     * @brief Calculate the Expression Result
     *
     * @return The Expression result
     */
    int calculate();

 private:
    /**
     * @brief Create a queue with all Expression tokens
     *
     * @return True if everything is ok, False if not
     */
    bool tokenize();

    /**
     * @brief Convert an infix expression to posfix
     *
     * @return True if all succeed, False otherwise
     */
    bool infix2posfix();

    std::string m_expr = "";       //!< A expression string
    Queue<Term> *m_terms;         //!< A pointer to a expression terms Queue
    Queue<Term> *m_terms_posfix;  //!< A pointer to a posfix expression Queue
};

#include "expression.inl"

#endif
