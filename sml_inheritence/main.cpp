//
// Created by N L on 15/02/2026.
//
#include <iostream>
#include <fstream>

#include "SMLInterpreter.h"

int main(int argc, char* argv[]) {
    std::string source {};
    if (argc > 1)
    {
        // Read file
        std::ifstream f(argv[1]);
        if (!f) {std::cerr << "Error opening file: " << argv[1] << "\n"; return 1;}

        source = {std::istreambuf_iterator<char>(f), {}};
        std::cout << "Running Program!\n";
        std::cout << "----------------------------------------------\n";
    } else {std::cerr << "Not enough args! \n"; return 1;}

    try
    {
        SMLInterpreter vm;
        vm.run_source(source);
    } catch (const std::exception& ex){
        std::cerr << "Runtime error: " << ex.what() << '\n';
        return 1;
    }


    return 0;
}
