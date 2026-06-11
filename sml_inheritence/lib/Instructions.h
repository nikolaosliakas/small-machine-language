#ifndef SMALL_MACHINE_LANGUAGE_INSTRUCTIONS_H
#define SMALL_MACHINE_LANGUAGE_INSTRUCTIONS_H
#pragma once
#include <string>


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

// Operation on operand stack
struct PushInstr :  Instruction {
    explicit PushInstr(const std::string& v) : Instruction(v){}
    std::string name() const override { return "push"; }
    int execute(Interpreter& vm, int pc) override {
        vm.push(std::stoi(operand_));
        return pc + 1;
    }
};
struct PopInstr :  Instruction {
    // no need for constructor, default constructor used
    std::string name() const override { return "pop"; }
    int execute(Interpreter& vm, int pc) override {
        vm.pop();
        return pc + 1;
    }
};
// Operations on loading and retrieving variables from symb table
struct LoadInstr : Instruction{
    explicit LoadInstr(const std::string& v) : Instruction(v){}
    std::string name() const override { return "load"; }
    int execute(Interpreter& vm, int pc) override {
        // loads the symboltable stored value and pushes that int onto the operand stack
        vm.push(vm.loadVar(operand_));
        return pc + 1;
    }
};

struct StoreInstr : Instruction{
    explicit StoreInstr(const std::string& v) : Instruction(v){}
    std::string name() const override { return "store"; }
    int execute(Interpreter& vm, int pc) override {
        // take top from the operand stack and store in the variable arg passed to operand_
        vm.store(operand_, vm.pop());
        return pc + 1;
    }
};

// Arithmatic Operations
struct AddInstr: Instruction{
    std::string name() const override {return "add";}
    int execute(Interpreter& vm, int pc) override{
        int b = vm.pop();
        int a = vm.pop();
        vm.push(a + b);
        return pc + 1;
    }
};
struct SubInstr: Instruction{
    std::string name() const override {return "sub";}
    int execute(Interpreter& vm, int pc) override{
        int b = vm.pop();
        int a = vm.pop();
        vm.push(a - b);
        return pc + 1;
    }
};
struct MulInstr: Instruction{
    std::string name() const override {return "mul";}
    int execute(Interpreter& vm, int pc) override{
        int b = vm.pop();
        int a = vm.pop();
        vm.push(a * b);
        return pc + 1;
    }
};

struct DivInstr: Instruction{
    std::string name() const override {return "div";}
    int execute(Interpreter& vm, int pc) override{
        int b = vm.pop();
        int a = vm.pop();
        if (b == 0) throw std::runtime_error("Division by zero!");
        vm.push(a / b);
        return pc + 1;
    }
};

struct RetInstr: Instruction{
    // This is where nesting occurs - the program either transfers to another Frame if ther eis one on the stack
    //  or it is finished
    std::string name() const override {return "return";}
    int execute(Interpreter& vm, int pc) override{
        bool hasVal = !vm.topFrame().stackEmpty();
        int retVal = hasVal ? vm.pop() : 0; // either return a value or 0 - expand later to Some/None handling?
        int nextPC = vm.leave(); // handy leaving the frame calls the return address to begin the program again after the return

        // test if exiting programming
        if (!vm.hasFrame()){
            // @main - done
            vm.setRunning(false);
            return nextPC;
        }
        if (hasVal) vm.push(retVal);
        return nextPC;
    }
};

struct InvokeInstr : Instruction{
    InvokeInstr(const std::string& m) : Instruction(m){};
    std::string name() const override {return "invoke";}
    int execute(Interpreter& vm, int pc) override{
        std::string mname = operand_;
        // if there is a name and it has a method char prefix remove the prefix...
        if (!mname.empty() && mname.front() == '@') mname = mname.substr(1);

        const MethodDef& mdef = vm.method(mname);
        // Collect args from current caller
            // example invoke listRange start end
            // collect start and end from the operandStack!
        std::vector<int> args;
        size_t mParamSize {mdef.params.size()};
        args.reserve(mParamSize);
        for (size_t i{0}; i < mParamSize; ++i)
            args.push_back(vm.pop());

        // Create new callee frame
        vm.enter(mname, pc + 1);

        // Bind params backward
        for (int i = static_cast<int>(mParamSize) - 1; i >= 0; --i)
            vm.store(mdef.params[i], args[i]);

        return mdef.startPC;
    }
};










#endif //SMALL_MACHINE_LANGUAGE_INSTRUCTIONS_H
