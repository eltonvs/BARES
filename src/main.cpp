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

/**
 * @brief Main function
 *
 * The main function, used to execute everything.
 */
int main(int argc, char const *argv[]) {
    std::ifstream input;
    std::ofstream output;

    if (argc > 2) {
        input.open("data/" + std::string(argv[1]));
        output.open("data/" + std::string(argv[2]));
    } else {
        std::cerr << "No file specified. Finishing execution.\n";
        return EXIT_FAILURE;
    }

    // Verify if the files aren't opened
    if (!input.is_open() || !output.is_open()) {
        std::cerr << "The file specified cannot be opened.\n";
        return EXIT_FAILURE;
    }

    // Close Opened files
    input.close();
    output.close();

    return EXIT_SUCCESS;
}
