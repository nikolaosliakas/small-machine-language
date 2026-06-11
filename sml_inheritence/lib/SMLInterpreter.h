#ifndef SMALL_MACHINE_LANGUAGE_SMLINTERPRETER_H
#define SMALL_MACHINE_LANGUAGE_SMLINTERPRETER_H
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include "Interpreter.h"

class SMLInterpreter : public Interpreter
{
public:
    void run_source(const std::string& src)
    {
        parse(src);
        // execute();
    }
private:
    std::string trimLine(std::string l) {
        l.erase(0, l.find_first_not_of(" \t\r\n"));
        auto last = l.find_last_not_of(" \t\r\n");
        if (last != std::string::npos) l = l.substr(0, last + 1);
        return l;
    }

    void parse(const std::string& src)
    {
        std::istringstream stream{src};
        std::string line{};

        while (std::getline(stream, line))
        {
            line = trimLine(std::move(line));
            if (line.empty()) continue; // don't process empty lines.
            std::istringstream ls(line);
            std::string tok;
            ls >> tok;

            // Three routes for each token - Method declaration, JumpLabel, Instruction
            // ----- Method Declaration
            if (tok.front() == '@'){
                std::cout << tok << "   :::: Method Declaration\n";
                continue;
            }
            // ----- Jump Label
            if (tok.back() == ':'){
                std::cout << tok << "   :::: Jump Label\n";
                continue;
            }

            // ----- Instruction
            // use the stream iterators to process the input stream
            std::vector operands((std::istream_iterator<std::string>(ls)),
                                      std::istream_iterator<std::string>());
            std::cout << tok << " inputs-------  " ;
            for (const std::string& op : operands)
                std::cout << op << " ";

            std::cout << "   :::::::::: Instruction\n";
        }
        // load program after all lines have been converted to stack machine
    }
};


#endif //SMALL_MACHINE_LANGUAGE_SMLINTERPRETER_H
