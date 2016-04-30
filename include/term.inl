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

// Gets Term Column
int Term::get_col() const {
    return m_col;
}

// Gets Term precedence
int Term::get_precedence() const {
    if (is_operand())
        switch(m_term[0]) {
            case '(':
            case ')':
                return 1;
            case 'u':
                return 2;
            case '^':
                return 3;
            case '*':
            case '/':
            case '%':
                return 4;
            case '+':
            case '-':
                return 5;
        }
    return -1;
}

// Gets the number integer value
bool Term::get_raw_number(int &_return) const {
    return is_number() ? (_return = atoi(m_term.c_str())) : false;
}

// Verify if the term is a number
bool Term::is_number() const {
    for (auto i = m_term[0] == '-' ? 1u : 0u; i < m_term.size(); i++)
        if (m_term[i] < 48 or m_term[i] > 57)
            return false;
    return true;
}

// Verify if the term is a valid number
bool Term::is_valid_number() const {
    if (m_term.size() > 6)  // Verify if is a too big number
        return false;
    int val;
    return get_raw_number(val) and val >= -32768 and val <= 32767;
}

// Verify if the term is an operand
bool Term::is_operand() const {
    if (m_term == "%" or m_term == "*" or m_term == "+" or
        m_term == "-" or m_term == "/" or m_term == "^")
        return true;
    return false;
}

// Verify if the term is an opening parenthesis
bool Term::is_opening_parenthesis() const {
    return m_term == "(";
}

// Verify if the term is a closing parenthesis
bool Term::is_closing_parenthesis() const {
    return m_term == ")";
}
