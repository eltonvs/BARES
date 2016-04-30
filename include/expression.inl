/*!
 *  @file expression.inl
 *  @brief Expression Implementations
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with Expression Class implementations
 */

#include "expression.hpp"
#include "term.hpp"

// Constructor
Expression::Expression(std::string _expr) : m_expr(_expr) {
    m_terms        = new Queue<Term>;
    m_terms_posfix = new Queue<Term>;
}

// Destructor
Expression::~Expression() {
    delete m_terms;
    delete m_terms_posfix;
}
