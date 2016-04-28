/*!
 *  @file terms.hpp
 *  @brief Terms Class Header
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with the Terms Class header
 */

#ifndef _terms_hpp_
#define _terms_hpp_

#include <string>
#include "queue.hpp"

/**
 * @brief Terms Class
 *
 * The Terms implementation.
 */
class Terms {
 public:
 private:
    std::string term = "";  //<! The term value
    int col = -1;           //<! The term column on expression
};

#include "terms.inl"

#endif
