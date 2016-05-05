/*!
 *  @mainpage BARES
 *  @author Elton de Souza Vieira
 *  @date April, 2016
 *  @copyright Copyright &copy; 2016. All rights reserved.
 *  @version 1.0
 *
 *  @file main.cpp
 *  @brief Main File
 *
 *  File with the main function
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

#include "stack.hpp"
#include "queue.hpp"
#include "term.hpp"
#include "errors.hpp"
#include "expression.hpp"

/**
 * @brief Main function
 *
 * The main function, used to execute everything.
 */
int main(int argc, char const *argv[]) {
    std::ifstream input;
    std::ofstream output;
    std::ostream *out;

    // Variables to file read
    std::string line = "";
    std::string result = "";

    if (argc >= 2) {
        input.open("data/" + std::string(argv[1]));
        // Verify if the files aren't opened
        if (!input.is_open()) {
            input.close();
            goto open_failure;
        }
        if (argc == 2) {
            out = &std::cout;
        } else {
            output.open("data/" + std::string(argv[2]));
            if (!output.is_open()) {
                output.close();
                goto open_failure;
            }
            out = &output;
        }
    } else {
        std::cerr << "No input file specified. Finishing execution.\n";
        return EXIT_FAILURE;
    }

    while (std::getline(input, line)) {
        Expression expr(line);
        expr.calculate(result);
        *out << result << "\n";
    }

    // Close Opened files
    input.close();
    output.close();

    return EXIT_SUCCESS;

    open_failure: {
        std::cerr << "The file specified cannot be opened.\n";
        return EXIT_FAILURE;
    }
}
