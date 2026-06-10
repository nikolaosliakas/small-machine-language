#ifndef SMALL_MACHINE_LANGUAGE_INTERPRETER_H
#define SMALL_MACHINE_LANGUAGE_INTERPRETER_H
#include <memory>
#include <unordered_map>

#include "Instructions.h"
#include "Method.h"


class Interpreter{
protected:
    std::vector<std::unique_ptr<Instruction>> program_;
    std::unordered_map<std::string, MethodDef> methods_;
    std::unordered_map<std::string, int> labels_;
    std::vector<Frame> callStack_;
    bool running_ = false;
public:
    virtual ~Interpreter() = default;

    void load(std::vector<std::unique_ptr<Instruction>> prog,
        std::unordered_map<std::string, MethodDef> methods,
        std::unordered_map<std::string, int> labels){
        program_ = std::move(prog);
        methods_ = std::move(methods);
        labels_ = std::move(labels);
    }

    // Ops on Frame stackDelegates to topFrame() AKA current Frame
    void push(int v) { topFrame().push(v);}
    int pop() {return topFrame().pop();}
    int peek() {return topFrame().peek();}

    // Ops on symbol_table within each topFrame


    // Call management


    Frame& topFrame(){
        if (callStack_.empty())
            throw std::runtime_error("No active frame");
        return callStack_.back();
    }


    
};

#endif //SMALL_MACHINE_LANGUAGE_INTERPRETER_H
