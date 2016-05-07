/*!
 *  @file expression.cpp
 *  @brief Expression Implementations
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with Expression Class implementations
 */

#include <iostream>
#include <cassert>
#include <string>

#include "stack.hpp"
#include "queue.hpp"
#include "errors.hpp"
#include "expression.hpp"
#include "term.hpp"

// Errors Array content initialization
std::string Errors::m_errors[] = {
    "Numeric constant out of range: column ",
    "Ill-formed expression or missing term detected: column ",
    "Invalid operand: column ",
    "Extraneous symbol: column ",
    "Mismatch ')': column ",
    "Lost operator: column ",
    "Missing closing ')' to match opening '(' at: column ",
    "Division by zero!",
    "Numeric overflow error!"
};

// Constructor
Expression::Expression(std::string _expr) : m_expr(_expr) {
    m_terms         = new Queue<Term>;
    m_terms_postfix = new Queue<Term>;
    m_error.id      = -1;
    m_error.col     = -1;
}

// Destructor
Expression::~Expression() {
    delete m_terms;
    delete m_terms_postfix;
}

// Tokenize
bool Expression::tokenize() {
    bool _was_number = false;
    bool _was_whitespace = false;
    bool _was_opening_parenthesis = false;
    bool _was_closing_parenthesis = false;
    bool _was_operator = false;
    int _parenthesis_diff = 0;
    int _fst_parenthesis = -1;

    Term t1, t2;
    for (auto i(0u); i < m_expr.size(); i++) {
        t2.set(m_expr[i], i);
        bool _is_number = is_number(t2);
        bool _is_operator = is_operator(t2);
        bool _is_opening_parenthesis = is_opening_parenthesis(t2);
        bool _is_closing_parenthesis = is_closing_parenthesis(t2);
        bool _is_parenthesis = (_is_opening_parenthesis || _is_closing_parenthesis);
        bool _is_last_operand = (i == m_expr.size() - 1);
        bool _is_whitespace = (t2.value == " ");
        bool _was_parenthesis = (_was_opening_parenthesis || _was_closing_parenthesis);

        // Verify if the current term is a whitespace
        if (_is_whitespace) {
            _was_whitespace = true;
            if (_is_last_operand) {
                if (_was_number) {
                    m_terms->enqueue(t1);
                    t1.value = "";
                } else if (!_was_closing_parenthesis) {
                    set_error(1, t2.col + 1);
                    return false;
                }
            }
            continue;
        // Verify if the current term is a number
        } else if (_is_number) {
            if ((_was_number && _was_whitespace) || _was_closing_parenthesis) {
                set_error(3, t2.col);
                return false;
            }
            if (_was_number) {
                t1.value += t2.value;
            } else {
                t1.set(t2.value, i);
            }
            if (!is_valid_number(t1)) {
                set_error(0, t1.col);
                return false;
            }
            if (_is_last_operand)
                m_terms->enqueue(t1);
            _was_number = true;
            _was_opening_parenthesis = false;
            _was_closing_parenthesis = false;
            _was_operator = false;
        // Verify if the current term is a operator or parenthesis
        } else if (_is_operator || _is_parenthesis) {
            if (_was_number) {
                m_terms->enqueue(t1);
                t1.value = "";
            }
            _fst_parenthesis = (_parenthesis_diff == 0) ? -1 : _fst_parenthesis;
            if (_is_parenthesis) {
                if (_parenthesis_diff == 0)
                    _fst_parenthesis = t2.col;
                _parenthesis_diff += _is_opening_parenthesis ? 1 : -1;
            }
            if (_parenthesis_diff < 0) {
                set_error(4, t2.col);
                return false;
            }
            if (!_was_number) {
                if (t2.value == "-") {
                    t2.is_unary = true;
                } else if (!_is_parenthesis && !_was_parenthesis) {
                    set_error(5, t2.col);
                    return false;
                }
            }
            if (_is_last_operand && !_is_parenthesis) {
                set_error(1, t2.col + 1);
                return false;
            }
            if (_is_opening_parenthesis && _was_closing_parenthesis) {
                set_error(3, t2.col);
                return false;
            }
            if (_is_closing_parenthesis && _was_opening_parenthesis) {
                set_error(1, t2.col);
                return false;
            }
            m_terms->enqueue(t2);
            _was_number = false;
            if (_is_operator) {
                _was_operator = true;
                _was_opening_parenthesis = false;
                _was_closing_parenthesis = false;
            } else {
                _was_operator = false;
                if (_is_opening_parenthesis) {
                    _was_opening_parenthesis = true;
                    _was_closing_parenthesis = false;
                } else {
                    _was_opening_parenthesis = false;
                    _was_closing_parenthesis = true;
                }
            }
        // Invalid Operand
        } else {
            set_error(_was_operator ? 1 : 2, t2.col);
            return false;
        }
        _was_whitespace = false;
    }

    if (_parenthesis_diff != 0) {
        set_error(6, _fst_parenthesis);
        return false;
    }

    std::cout << *m_terms << "\n";

    return true;
}

bool Expression::infix2postfix() {
    Stack<Term> operators;
    Queue<Term> *cpy = m_terms;
    Term t1, t2;
    // Verify all terms on queue
    while (!cpy->isEmpty()) {
        cpy->dequeue(t1);
        if (is_number(t1)) {
            m_terms_postfix->enqueue(t1);
        } else {
            if (operators.isEmpty()) {
                operators.push(t1);
            } else if (is_closing_parenthesis(t1)) {
                operators.top(t2);
                while (!is_opening_parenthesis(t2) && !operators.isEmpty()) {
                    operators.pop(t2);
                    m_terms_postfix->enqueue(t2);
                    operators.top(t2);
                }
                operators.pop(t2);
            } else {
                operators.top(t2);
                while (get_precedence(t1) > get_precedence(t2) && !operators.isEmpty() && !is_opening_parenthesis(t2)) {
                    operators.pop(t2);
                    if (!is_opening_parenthesis(t2))
                        m_terms_postfix->enqueue(t2);
                    operators.top(t2);
                }
                operators.push(t1);
            }
        }
    }
    // Remove remaining terms on Stack
    while (!operators.isEmpty()) {
        operators.pop(t2);
        if (!is_opening_parenthesis(t2))
            m_terms_postfix->enqueue(t2);
    }

    std::cout << *m_terms_postfix << std::endl;

    return true;
}

// Calculate
bool Expression::calculate(std::string &_return) {
    if (!tokenize()) {
        _return = Errors::get_error_message(m_error.id, m_error.col);
        return false;
    }
    if (!infix2postfix()) {
        _return = Errors::get_error_message(m_error.id, m_error.col);
        return false;
    }
    _return = "Expression result";
    return true;
}

// Sets the Error
void Expression::set_error(const int _id, const int _col) {
    m_error.id  = _id;
    m_error.col = _col;
}


// Gets Term precedence
int Expression::get_precedence(Term _t) const {
    if (is_operator(_t)) {
        if (_t.value == "-" and _t.is_unary)
            return 2;
        switch(_t.value[0]) {
            case '(':
            case ')':
                return 1;
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
    }
    return -1;
}

// Gets Term integer value
bool Expression::get_int_number(Term _t, int &_return) const {
    return is_number(_t) ? (_return = atoi(_t.value.c_str())) : false;
}

// Verify if the Term is a number
bool Expression::is_number(Term _t) const {
    for (auto i = _t.value[0] == '-' ? 1u : 0u; i < _t.value.size(); i++)
        if (_t.value[i] < 48 or _t.value[i] > 57)
            return false;
    return true && !is_operator(_t);
}

// Verify if the Term is a valid number
bool Expression::is_valid_number(Term _t) const {
    if (_t.value.size() > 6)  // Verify if is a too big number
        return false;
    int val;
    return get_int_number(_t, val) and val >= -32768 and val <= 32767;
}

// Verify if the Term is a operator
bool Expression::is_operator(Term _t) const {
    if (_t.value == "%" or _t.value == "*" or _t.value == "+" or
        _t.value == "-" or _t.value == "/" or _t.value == "^")
        return true;
    return false;
}

// Verify if the Term is a opening parenthesis
bool Expression::is_opening_parenthesis(Term _t) const {
    return _t.value == "(";
}

// Verify if the Term is a closing parenthesis
bool Expression::is_closing_parenthesis(Term _t) const {
    return _t.value == ")";
}

// Temporary method just for debug the class Methods
void Expression::tests() {
    Term t1("2", 1);
    Term t2("+", 1);
    int aux;

    assert(get_precedence(t1) == -1);
    assert(get_precedence(t2) == 5);
    assert(get_int_number(t1, aux) == true);

    assert(aux == 2);
    assert(get_int_number(t2, aux) == false);

    assert(is_number(t1) == true);
    assert(is_number(t2) == false);

    assert(is_valid_number(t1) == true);
    assert(is_valid_number(t2) == false);

    assert(is_operator(t1) == false);
    assert(is_operator(t2) == true);

    assert(is_opening_parenthesis(t1) == false);
    assert(is_opening_parenthesis(t2) == false);

    assert(is_closing_parenthesis(t1) == false);
    assert(is_closing_parenthesis(t2) == false);
}
