/*!
 *  @file term.hpp
 *  @brief Term struct Declaration
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with the Term Struct header
 */

#ifndef _term_hpp_
#define _term_hpp_

#include <string>
#include "queue.hpp"

/**
 * @brief The Term struct
 *
 * The Term struct implementation
 */
struct Term {
    std::string value = "";  //!< The term value
    int col = -1;            //!< The term column
    bool is_unary = false;   //!< Flag to indicate if is a unary operator

    /**
     * @brief Term Constructor
     * @param _val The Term value (to fit value variable)
     * @param _col The Term column (to fit col variable)
     *
     * The Term Constructor function
     */
    explicit Term(std::string _val = "", int _col = -1) : value(_val), col(_col) {}

    /**
     * @brief Term Setter
     * @param _val The Term value (to fit value variable)
     * @param _col The Term column (to fit col variable)
     *
     * The Term Setter function
     */
    template <typename str>
    void set(str _val = "", int _col = -1, bool _unr = false) {
        value = _val;
        col = _col;
        is_unary = _unr;
    }
};

/**
 * @brief Overload << operator to Terms
 * @param _os The std::ostream
 * @param _term The Term to be showed
 */
std::ostream &operator<<(std::ostream &_os, const Term &_term) {
    return _os << "\"" << _term.value << "\"";
}

#endif
