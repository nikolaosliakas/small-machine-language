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
        execute();
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

        // Keep track of labels, methods and program
        std::unordered_map<std::string, MethodDef> methods; // MethodDef contains the name, params and startpos in the pc
        std::unordered_map<std::string, int> labels; // values are program counter places
        std::vector<std::unique_ptr<Instruction>> prog;

        std::string currentMethod;

        while (std::getline(stream, line))
        {
            line = trimLine(std::move(line));
            if (line.empty()) continue; // don't process empty lines.
            std::istringstream ls(line);
            std::string tok;
            ls >> tok;

            // Three routes for each token - Method declaration, JumpLabel, Instruction
            // ----- Method Declaration @methodName [params. . ] -----
            if (tok.front() == '@'){
                currentMethod = tok.substr(1);
                if (!currentMethod.empty() && currentMethod.back() == ':')
                    currentMethod.pop_back();
                MethodDef md;
                md.name = currentMethod;
                md.startPC = static_cast<int>(prog.size());
                // read each parameter of a method
                std::string p;
                while (ls >> p) md.params.push_back(p);

                methods[currentMethod] = md;
                prog.push_back(std::make_unique<NopInstr>());
                continue;
            }
            // ----- Jump Label L<n>: ----
            if (tok.back() == ':'){
                std::string lbl = tok.substr(0, tok.size()-1);
                labels[lbl] = static_cast<int>(prog.size());
                std::string nextOp;
                std::string nextOperand; // TODO expand for multiple operands in an instruction!
                if (ls >> nextOp){
                    ls >> nextOperand;
                    prog.push_back(buildInstruction(nextOp, nextOperand));
                } else {
                    prog.push_back(std::make_unique<NopInstr>());
                }
                continue;
            }

            // ----- Instruction
            std::string operand;
            ls >> operand;
            prog.push_back(buildInstruction(tok, operand));
        }
        // load program after all lines have been converted to stack machine
        load(std::move(prog), std::move(methods), std::move(labels));
    }

    std::unique_ptr<Instruction> buildInstruction(const std::string& op, const std::string& operand) {
        if (op == "push") return std::make_unique<PushInstr>(operand);
        if (op == "pop") return std::make_unique<PopInstr>();
        if (op == "load") return std::make_unique<LoadInstr>(operand);
        if (op == "store") return std::make_unique<StoreInstr>(operand);
        if (op == "add") return std::make_unique<AddInstr>();
        if (op == "sub") return std::make_unique<SubInstr>();
        if (op == "mul") return std::make_unique<MulInstr>();
        if (op == "div") return std::make_unique<DivInstr>();
        if (op == "return") return std::make_unique<RetInstr>();
        if (op == "if_cmpgt") return std::make_unique<IfCmpGtInstr>(operand);
        if (op == "if_cmplt") return std::make_unique<IfCmpLtInstr>(operand);
        if (op == "if_cmpgte") return std::make_unique<IfCmpGteInstr>(operand);
        if (op == "if_cmplte") return std::make_unique<IfCmpLteInstr>(operand);
        if (op == "goto") return std::make_unique<GoToInstr>(operand);
        if (op == "invoke") return std::make_unique<InvokeInstr>(operand);
        if (op == "print") return std::make_unique<PrintInstr>();
        throw std::runtime_error("This is an unknown operation: " + op);
    }

    void execute(){
        if (!methodExists("main"))
            throw std::runtime_error("No @main method found in program!");
        const MethodDef& mainDef = method("main");
        enter("main", programSize());
        setRunning(true);
        int pc = mainDef.startPC;
        // if return address is past end then stop!
        while (isRunning() && pc < programSize()){
            // find pointer of Instruction in program at pc count
            pc = instrAt(pc)->execute(*this, pc);
        }
    }
};


#endif //SMALL_MACHINE_LANGUAGE_SMLINTERPRETER_H
