#ifndef SMALL_MACHINE_LANGUAGE_INSTRUCTIONS_H
#define SMALL_MACHINE_LANGUAGE_INSTRUCTIONS_H
#pragma once
#include <string>
#include <utility>

// Forward declaration — enough for the signature inside the struct
class Interpreter;

class Instruction {
protected:
    std::string operand_;
public:
    explicit Instruction(std::string operand = {}) : operand_(std::move(operand)) {}
    virtual ~Instruction() = default;
    virtual int execute(Interpreter& vm, int pc) = 0;
    virtual std::string name() const = 0;
    std::string& operand() { return operand_; }
};

struct PushInstr : public Instruction {
    using Instruction::Instruction;
    std::string name() const override { return "push"; }
    int execute(Interpreter& vm, int pc) override; // Body deferred
};


// ---- Define the body down here, inline ----
inline int PushInstr::execute(Interpreter& vm, int pc) {
    vm.push(std::stoi(operand_));
    return pc + 1;
}

#endif //SMALL_MACHINE_LANGUAGE_INSTRUCTIONS_H
