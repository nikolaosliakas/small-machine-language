#ifndef SMALL_MACHINE_LANGUAGE_INTERPRETER_H
#define SMALL_MACHINE_LANGUAGE_INTERPRETER_H
#include <csignal>
#include <memory>
#include <unordered_map>
#include "Method.h"

class Instruction;

class Interpreter{
protected:
    std::vector<std::unique_ptr<Instruction>> program_;
    std::unordered_map<std::string, MethodDef> methods_;
    std::unordered_map<std::string, int> labels_;
    std::vector<Frame> callStack_;
    bool running_ = false;
public:
    virtual ~Interpreter();

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
    void store(const std::string& name, int v) {topFrame().symbols().set(name, v);}
    int loadVar(const std::string& name) {return topFrame().symbols().get(name);}
    // Call management
    void enter(const std::string& methodName, int returnPC){
        callStack_.emplace_back(methodName, returnPC);
    }
    int leave(){
        int ret = topFrame().returnAddr();
        callStack_.pop_back();
        return ret;
    }
    std::size_t callDepth() const { return callStack_.size(); }
    bool hasFrame() const{ return !callStack_.empty(); }

    Frame& topFrame(){
        if (callStack_.empty())
            throw std::runtime_error("No active frame");
        return callStack_.back();
    }

    // Lookups for labels and MethodNames
    int labelPC(const std::string& lbl) const{
        auto it = labels_.find(lbl);
        if (it == labels_.end())
            throw std::runtime_error("Unknown label: " + lbl);
        return it->second;
    }
    const MethodDef& method(const std::string& name) const{
        auto it = methods_.find(name);
        if (it == methods_.end())
            throw std::runtime_error("Unknown method: " + name);
        return it->second;
    }
    bool methodExists(const std::string& name) const {
        return methods_.contains(name);
    }
    // Program Access - and running state
    int programSize() const { return static_cast<int>(program_.size());}
    // fetches the instruction at the program count within the program dynamic array
    Instruction* instrAt(int pc) const {return program_.at(pc).get(); }

    void setRunning(bool r){running_ = r;}
    bool isRunning() const {return running_; }
};
// This needed the full definition of Instruction for the destructor as the std::vector with unique pointers needs the WHOLE definition
// when it is defined!
#include "Instructions.h"

inline Interpreter::~Interpreter() = default;

#endif //SMALL_MACHINE_LANGUAGE_INTERPRETER_H
