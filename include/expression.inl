/*!
 *  @file expression.inl
 *  @brief Expression Implementations
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with Expression Class implementations
 */

#include "expression.hpp"
#include "terms.hpp"

// Constructor
Expression::Expression(std::string _expr) {
    m_expr         = _expr;
    m_terms        = new Queue<Terms>;
    m_terms_posfix = new Queue<Terms>;
}

// Destructor
Expression::~Expression() {
    delete m_terms;
    delete m_terms_posfix;
}
