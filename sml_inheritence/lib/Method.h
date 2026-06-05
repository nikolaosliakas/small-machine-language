#ifndef SMALL_MACHINE_LANGUAGE_METHOD_H
#define SMALL_MACHINE_LANGUAGE_METHOD_H
#include <iostream>
/*
 * Each Method contains its definition, a stack frame activation record for one call and a Symbol table
 *
 */
struct MethodDef
{
    std::string name;
    std::vector<std::string> params;
    int start_pc; // initial program counter
};

// Each Frame stores variables in a symboltable
class SymbolTable
{
    std::unordered_map<std::string, int> vars_;
public:
    void set(const std::string& name, int value){ vars_[name] = value;}
    int get(const std::string& name) const
    {
        const auto it = vars_.find(name);
        if (it == vars_.end())
            throw std::runtime_error("Undefined variable: " + name);
        return it->second;
    }
    bool has(const std::string& name ) const {return vars_.count(name) > 0;}
    // void dump(std::ostream& os = std::cout) const
    void dump() const{
        std::cout << " [SymbolTable]\n";
        for (auto& [k, v] : vars_)
            std::cout << "  " << k << " = " << v << '\n';}
};

//Frame - activation record for one method call
class Frame{
    std::string methodName_;
    int returnAddr_; // subscript in the flat instruction list
    std::vector<int> operand_stack_;
    SymbolTable symbols_;
public:
    Frame(std::string name, int ret)
        : methodName_(std::move(name)), returnAddr_(ret) {}
    void push(const int v) {operand_stack_.push_back(v); }
    int pop(){
        if (operand_stack_.empty())
            throw std::runtime_error("Stack underflow in frame '" + methodName_ + "'");
        int v = operand_stack_.back();
        operand_stack_.pop_back();
        return v;
    }
    int peek() const{
        if (operand_stack_.empty())
            throw std::runtime_error("Stack underflow (peek) in frame '" + methodName_ + "'");
        return operand_stack_.back();
    }

    bool stackEmpty() const {return operand_stack_.empty();}
    // Symbol Table Delegation - const and mutable delegated references
    SymbolTable& symbols(){return symbols_;}
    const SymbolTable& symbols() const {return symbols_;}
    // Accessors
    const std::string& name() const {return methodName_;};
    int returnAddr() const{ return returnAddr_;}

    void dump() const
    {
        std::cout << "Frame[" << methodName_ << "] ret=" << returnAddr_ << '\n';
        symbols_.dump();
    }
};


#endif //SMALL_MACHINE_LANGUAGE_METHOD_H
