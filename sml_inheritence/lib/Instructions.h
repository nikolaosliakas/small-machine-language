#ifndef SMALL_MACHINE_LANGUAGE_INSTRUCTIONS_H
#define SMALL_MACHINE_LANGUAGE_INSTRUCTIONS_H
#include <string>
#include <vector>

/**
 * Current Grammar:
 *  add
 *
 */
// forward declaration
class Interpreter;

class Instruction{
protected:
    std::vector<std::string> operands_;
public:
    explicit Instruction(std::vector<std::string> operands = {}): operands_(std::move(operands)) {}
    virtual ~Instruction() = default;

    virtual int execute(Interpeter& vm, int pc) = 0;
    // The attribute stops compilation if name is called but the result is nto stored.
     [[nodiscard]] virtual std::string name() const = 0;

    std::vector<std::string>& operands() {return operands_;}
};



#endif //SMALL_MACHINE_LANGUAGE_INSTRUCTIONS_H
