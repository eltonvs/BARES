/*!
 *  @file expression.cpp
 *  @brief Expression Implementations
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with Expression Class implementations
 */

#include <iostream>
#include <cassert>
#include <cmath>
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
                if (t2.value == "-" && !_was_closing_parenthesis) {
                    t2.is_unary = true;
                } else if (!_is_parenthesis && !_was_parenthesis) {
                    set_error(5, t2.col);
                    return false;
                } else if (_was_operator && _is_closing_parenthesis) {
                    set_error(1, t2.col);
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

    return true;
}

bool Expression::infix2postfix() {
    Stack<Term> *operators = new Stack<Term>;
    Term t1, t2;
    // Verify all terms on queue
    while (!m_terms->isEmpty()) {
        m_terms->dequeue(t1);
        operators->top(t2);
        // If is a number, send to postfix queue
        if (is_number(t1)) {
            m_terms_postfix->enqueue(t1);
        // If isn't a number and the queue is empty or is
        // an opening parenthesis, send to operators stack
        } else if (operators->isEmpty() || is_opening_parenthesis(t1)) {
            // If the tokenize is right, this never should happen
            if (is_closing_parenthesis(t1)) {
                set_error(4, t1.col);
                delete operators;
                return false;
            }
            operators->push(t1);
        // If is a closing parenthesis, send all the operators
        // until the opening parenthesis to postfix queue
        } else if (is_closing_parenthesis(t1)) {
            while (!is_opening_parenthesis(t2)) {
                operators->pop(t2);
                m_terms_postfix->enqueue(t2);
                operators->top(t2);
            }
            assert(is_opening_parenthesis(t2));
            operators->pop(t2);
        // Else, remove all operators who have a minor
        // precedence and push him to operators stack
        } else {
            while (get_precedence(t1) >= get_precedence(t2) &&
                   !operators->isEmpty() && !is_opening_parenthesis(t2)) {
                operators->pop(t2);
                m_terms_postfix->enqueue(t2);
                operators->top(t2);
            }
            operators->push(t1);
        }
    }
    // Remove remaining terms on Stack
    while (!operators->isEmpty()) {
        operators->pop(t2);
        // If the tokenize is right, this never should happen
        if (is_opening_parenthesis(t2)) {
            set_error(6, t2.col);
            delete operators;
            return false;
        }
        m_terms_postfix->enqueue(t2);
    }

    // Delete operators Stack to avoid memory leak
    delete operators;

    return true;
}

// Calculate
bool Expression::calculate(std::string &_return) {
    Term result;

    // Try to do all operations
    if (!tokenize() || !infix2postfix() || !get_result(result)) {
        _return = Errors::get_error_message(m_error.id, m_error.col);
        return false;
    }

    _return = result.value;
    return true;
}

bool Expression::get_result(Term &_return) {
    Stack<Term> *operands = new Stack<Term>;
    Term t1, t2, t3;

    while (!m_terms_postfix->isEmpty()) {
        m_terms_postfix->dequeue(t1);
        // If is a number, push him to the operands Stack
        if (is_number(t1)) {
            operands->push(t1);
        } else {
            operands->pop(t2);
            // If is unary, set the first term as 0
            if (t1.is_unary) {
                t3.value = "0";
            } else {
                operands->pop(t3);
            }
            // Try to apply operation
            if (apply_operation(t3, t2, t1, t2)) {
                operands->push(t2);
            } else {
                delete operands;
                return false;
            }
        }
    }

    operands->pop(_return);

    // Delete operands Stack to avoid memory leak
    delete operands;

    return true;
}

// Aplly Operation
bool Expression::apply_operation(Term _t1, Term _t2, Term _op, Term &_rst) {
    if (is_operator(_op)) {
        int result, v1, v2;
        if (!is_valid_number(_t1) || !is_valid_number(_t2)) {
            set_error(8);
            return false;
        }
        get_int_number(_t1, v1);
        get_int_number(_t2, v2);
        switch (_op.value[0]) {
            case '^':
                result = std::pow(v1, v2);
                break;
            case '*':
                result = v1 * v2;
                break;
            case '/':
                if (v2 == 0) {
                    set_error(7);
                    return false;
                }
                result = v1 / v2;
                break;
            case '%':
                if (v2 == 0) {
                    set_error(7);
                    return false;
                }
                result = v1 % v2;
                break;
            case '+':
                result = v1 + v2;
                break;
            case '-':
                result = v1 - v2;
                break;
        }
        _rst.value = std::to_string(result);
        if (!is_valid_number(_rst)) {
            set_error(8);
            return false;
        }
        return true;
    }

    return false;
}

// Sets the Error
void Expression::set_error(const int _id, const int _col) {
    m_error.id  = _id;
    m_error.col = _col;
}


// Gets Term precedence
int Expression::get_precedence(Term _t) const {
    if (is_opening_parenthesis(_t) || is_closing_parenthesis(_t))
        return 1;
    if (is_operator(_t)) {
        if (_t.value == "-" && _t.is_unary)
            return 2;
        switch (_t.value[0]) {
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
    _return = atoi(_t.value.c_str());
    return is_number(_t);
}

// Verify if the Term is a number
bool Expression::is_number(Term _t) const {
    for (auto i = _t.value[0] == '-' ? 1u : 0u; i < _t.value.size(); i++)
        if (_t.value[i] < 48 or _t.value[i] > 57)
            return false;
    return !is_operator(_t);
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
