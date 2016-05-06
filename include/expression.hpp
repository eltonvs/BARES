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
     * @param _return The Expression result or error message
     *
     * @return True if al succeed, False if not
     */
    bool calculate(std::string &_return);

    /**
     * @brief Temporary Method
     *
     * @return Just for debugging
     */
    void tests();

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

    /**
     * @brief Function to set error
     * @param _id The error id
     * @param _col The error col
     *
     * Sets the error
     */
    void set_error(const int _id = -1, const int _col = -1);

    /**
     * @brief Gets the operand precedence
     * @param _t The term to be used on function
     * @return A integer with the operand precedence
     * @see is_operand
     *
     * Gets the operand precedence using that table:
     *
     * |  Operator  |  Precedence  |
     * |  :------:  |  :--------:  |
     * |  ( )       |  1           |
     * |  - (unary) |  2           |
     * |  ^         |  3           |
     * |  / * %     |  4           |
     * |  + -       |  5           |
     */
    int get_precedence(Term _t) const;

    /**
     * @brief Gets the integer value from a Term
     * @param _t The term to be used on function
     * @param _return The var to keep the returned value
     * @return True if all succeed, False otherwise
     *
     * Gets the Term integer value
     */
    bool get_int_number(Term _t, int &_return) const;

    /**
     * @brief Verify if the term value is a number
     * @param _t The term to be used on function
     * @return True if is a number, False otherwise
     *
     * Verify if is a number
     */
    bool is_number(Term _t) const;

    /**
     * @brief Verify if the term value is a valid number
     * @param _t The term to be used on function
     * @return True if is valid, False otherwise
     * @see is_number
     *
     * Verify if is a valid number (in range [-32.768, 32.767])
     */
    bool is_valid_number(Term _t) const;

    /**
     * @brief Verify if the Term is an expression operator
     * @param _t The term to be used on function
     * @return True if is an operator, False otherwise
     *
     * Verify if is a operator (+, -, /, *, ^, %)
     */
    bool is_operator(Term _t) const;

    /**
     * @brief Verify if the Term is a opening parenthesis
     * @param _t The term to be used on function
     * @return True if is an opening parenthesis, False if not
     * @see is_closing_parenthesis
     *
     * Verify if is a opening parenthesis
     */
    bool is_opening_parenthesis(Term _t) const;

    /**
     * @brief Verify if the Term is an closing parenthesis
     * @param _t The term to be used on function
     * @return True if is a closing parenthesis, False if not
     * @see is_opening_parenthesis
     *
     * Verify if is a closing parenthesis
     */
    bool is_closing_parenthesis(Term _t) const;

    //! The error structure
    struct {
        int id = -1;   //!< The error code
        int col = -1;  //!< The error code
    } m_error;
    std::string m_expr = "";      //!< A expression string
    Queue<Term> *m_terms;         //!< A pointer to a expression terms Queue
    Queue<Term> *m_terms_posfix;  //!< A pointer to a posfix expression Queue
};

#include "expression.inl"

#endif
