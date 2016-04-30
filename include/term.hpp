/*!
 *  @file term.hpp
 *  @brief Term Class Header
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with the Term Class header
 */

#ifndef _term_hpp_
#define _term_hpp_

#include <string>
#include "queue.hpp"

/**
 * @brief Term Class
 *
 * The Term implementation.
 */
class Term {
 public:
    /**
     * @brief Term Constructor
     * @param _term Receives the Term content
     * @param _col Receives the Term column
     *
     * Creates a Term
     */
    explicit Term(std::string _term = "", int _col = -1);

    /**
     * @brief Term Destructor
     *
     * Destroy a Term
     */
    ~Term();

    /**
     * @brief Getter to m_col
     * @return The Term col
     *
     * Get the Term col
     */
    int get_col() const;

    /**
     * @brief Gets the operand precedence
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
    int get_precedence() const;

    /**
     * @brief Getts the integer value from number
     * @param _return The var to keep the returned value
     * @return True if all succeed, False otherwise
     *
     * Get the number integer value
     */
    bool get_raw_number(int &_return) const;

    /**
     * @brief Verify if the term is an expression number
     * @return True if is a number, False otherwise
     *
     * Verify if is a number
     */
    bool is_number() const;

    /**
     * @brief Verify if the term is a valid number
     * @return True if is valid, False otherwise
     *
     * Verify if is a valid number (in range [-32.768, 32.767])
     */
    bool is_valid_number() const;

    /**
     * @brief Verify if the Term is an expression operand
     * @return True if is an operand, False otherwise
     *
     * Verify if is a operand (+, -, /, *, ^, %)
     */
    bool is_operand() const;

    /**
     * @brief Verify if the Term is an expression operand
     * @return True if is an opening parenthesus, False if not
     * @see is_closing_parenthesis
     *
     * Verify if is a opening parenthesis
     */
    bool is_opening_parenthesis() const;

    /**
     * @brief Verify if the Term is an coling parenthesis
     * @return True if is a closing parenthesis, False if not
     * @see is_opening_parenthesis
     *
     * Verify if is a closing parenthesis
     */
    bool is_closing_parenthesis() const;

 private:
    std::string m_term = "";  //<! The term value
    int m_col = -1;           //<! The term column on expression
};

#include "term.inl"

#endif
