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

// Tokenize
bool Expression::tokenize() {
    std::cout << m_expr << std::endl;

    bool _was_number = false;
    int _parenthesis_diff = 0;

    Term t1, t2;
    for (auto i(0u); i < m_expr.size(); i++) {
        t2.value = m_expr[i];
        t2.col = i;
        bool _is_number = is_number(t2);
        bool _is_operator = is_operator(t2);
        bool _is_opening_parenthesis = is_opening_parenthesis(t2);
        bool _is_closing_parenthesis = is_closing_parenthesis(t2);
        bool _is_last_operand = (i == m_expr.size() - 1);
        bool _is_whitespace = (t2.value == " ");

        std::cout << "[" << i << "]" << (_is_last_operand ? " (last): " : ": ");
        if (_is_whitespace) {
            std::cout << "Ignoring...\n";
        } else if (_is_number && !_is_operator) {
            std::cout << "Number read...";
            if (!is_valid_number(t2)) {
                std::cout << " But is invalid...\n";
                std::cout << Errors::get_error_message(2, t2.col) << std::endl;
                return false;
            }
            std::cout << " And is valid...\n";
            if (_was_number)
                t1.value += t2.value;
            else
                t1.value = t2.value, t1.col = i;
            _was_number = true;
            if (_is_last_operand)
                m_terms->enqueue(t1);
        } else if (_is_operator || _is_opening_parenthesis || _is_closing_parenthesis) {
            if (_was_number) {
                m_terms->enqueue(t1);
                t1.value = "";
            }
            if (_is_opening_parenthesis) {
                _parenthesis_diff++;
            } else if (_is_closing_parenthesis) {
                _parenthesis_diff--;
            }
            if (_parenthesis_diff < 0) {
                std::cout << Errors::get_error_message(4, t2.col) << std::endl;
                return false;
            }
            if (!_was_number) {
                if (t2.value == "-") {
                    t2.is_unary = true;
                } else if (!_is_opening_parenthesis && !_is_closing_parenthesis) {
                    std::cout << Errors::get_error_message(2, t2.col) << std::endl;
                    return false;
                }
            }
            m_terms->enqueue(t2);
            std::cout << "Operator read..." << std::endl;
            _was_number = false;
        } else {
            std::cout << Errors::get_error_message(3, t2.col) << std::endl;
            return false;
        }
    }

    if (_parenthesis_diff != 0) {
        std::cout << Errors::get_error_message(6, 0) << std::endl;
    }

    std::cout << "m_terms = " << *m_terms << std::endl;

    return true;
}

// Calculate
int Expression::calculate() {
    if (tokenize()) {
        // Do some magic here

        return true;
    }
    return false;
}

// Gets Term precedence
int Expression::get_precedence(Term _t) const {
    if (is_operator(_t))
        switch(_t.value[0]) {
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

// Gets Term integer value
bool Expression::get_int_number(Term _t, int &_return) const {
    return is_number(_t) ? (_return = atoi(_t.value.c_str())) : false;
}

// Verify if the Term is a number
bool Expression::is_number(Term _t) const {
    for (auto i = _t.value[0] == '-' ? 1u : 0u; i < _t.value.size(); i++)
        if (_t.value[i] < 48 or _t.value[i] > 57)
            return false;
    return true;
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
