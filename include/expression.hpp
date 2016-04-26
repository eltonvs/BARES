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
#include "terms.hpp"

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

 private:
    std::string m_expr = "";      //!< A expression string
    Queue<Terms> m_terms;         //!< A Queue of expression terms
    Queue<Terms> m_terms_posfix;  //!< A Queue of expression terms (posfix)
};

#include "expression.inl"

#endif
