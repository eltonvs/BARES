/*!
 *  @file errors.hpp
 *  @brief Errors Class Header
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *
 *  File with the Errors Class header
 */

#ifndef _errors_hpp_
#define _errors_hpp_

#include <string>
#include "queue.hpp"
#include "term.hpp"

/**
 * @brief Errors Class
 *
 * The Errors class (don't need to be instanciated)
 */
class Errors {
 public:
    /**
     * @brief Errors Constructor
     *
     * Delete Constructor
     */
    Errors() = delete;

    /**
     * @brief Errors Destructor
     *
     * Delete Destructor
     */
    ~Errors() = delete;

    /**
     * @brief Print An error message
     * @param _id  Error ID
     * @param _col Column where the error is
     *
     * @return String with the error message
     */
    static std::string get_error_message(unsigned _id, int _col = -1) {
        std::string _return = "";
        if (_id > 8)
            return _return;
        _return = m_errors[_id];
        if (_id <= 6)
            _return += std::to_string(_col + 1) + ".";
        return _return;
    }

 private:
    /**
     * @brief A vector of Errors Messages
     */
    static std::string m_errors[9];
};

#endif
