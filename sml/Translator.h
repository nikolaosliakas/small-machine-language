//
// Created by N L on 15/02/2026.
//

#ifndef SMALL_MACHINE_LANGUAGE_TRANSLATOR_H
#define SMALL_MACHINE_LANGUAGE_TRANSLATOR_H
#include <iostream>
#include <fstream>

class Translator {
public:
    static void readAndTranslate(const std::string_view fileName) {

        std::ifstream file{fileName};
        if (!file.is_open()) {
            std::cerr << "Error: Could not open the file " << fileName << '\n';
            return;
        }

        std::string line{};
        while (std::getline(file, line)) {
            std::cout << line << '\n';
        }


    }
};


#endif //SMALL_MACHINE_LANGUAGE_TRANSLATOR_H