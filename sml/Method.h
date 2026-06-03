#ifndef SMALL_MACHINE_LANGUAGE_METHOD_H
#define SMALL_MACHINE_LANGUAGE_METHOD_H

#include <string>
#include <stdexcept>
#include <vector>

class Method {

    std::vector<>

public:
    struct Identifier {
        std::string m_string;
        explicit Identifier(std::string_view name) : m_string (name) {
            if (name[0] != '@')
                throw std::invalid_argument("Method identifier name must start with @");
        }
    };





};

#endif //SMALL_MACHINE_LANGUAGE_METHOD_H