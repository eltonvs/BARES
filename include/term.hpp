/*!
 *  @file term.hpp
 *  @brief Term struct Header
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with the Term Struct header
 */

#ifndef _term_hpp_
#define _term_hpp_

#include <string>
#include "queue.hpp"

struct Term {
    std::string value = "";
    int col = -1;

    Term(std::string _val = "", int _col = -1) : value(_val), col(_col) {}
};

#endif
