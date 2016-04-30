/*!
 *  @file term.inl
 *  @brief Term Implementations
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with Term Class implementations
 */

#include "term.hpp"

// Constructor
Term::Term(std::string _term, int _col) : m_term(_term), m_col(_col) {}

// Destructor
Term::~Term() {
    m_term.clear();
}
