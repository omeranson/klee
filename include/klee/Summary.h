#ifndef KLEE_SUMMARY_H
#define KLEE_SUMMARY_H

#include <map>
#include <string>
#include <vector>
#include <ostream>

#include "klee/Common.h"
#include "klee/Constraints.h"

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>


class Summary {
    // ...
protected:
    bool _hasReturnValue;
    klee::ref<klee::Expr> _returnValue;
    std::map<klee::ref<klee::Expr>, klee::ref<klee::Expr> > _modifiedMemory;
    std::map<klee::ref<klee::Expr>, klee::ref<klee::Expr> > _stackMemory;
    std::map<const llvm::GlobalValue*, klee::ref<klee::Expr> > _globals;
    std::map<const llvm::Value*, klee::ref<klee::Expr> > _values;
    std::vector<klee::ref<klee::Expr> > _arguments;
    std::string _functionName;
    llvm::Function const * _function;
    llvm::Module const * _module;

    virtual void updateWithInstruction(const llvm::Instruction & instruction);
    virtual void updateWithInstruction(const llvm::ReturnInst & instruction);
    /*
    virtual void updateWithInstruction(const llvm::BranchInst & instruction);
    virtual void updateWithInstruction(const llvm::SwitchInst & instruction);
    virtual void updateWithInstruction(const llvm::InvokeInst & instruction);
    virtual void updateWithInstruction(const llvm::CallInst & instruction);
    virtual void updateWithInstruction(const llvm::PHINode & instruction);
    virtual void updateWithInstruction(const llvm::SelectInst & instruction);
    virtual void updateWithInstruction(const llvm::BinaryOperator & instruction);
    virtual void updateWithInstruction(const llvm::UnaryInstruction & instruction);
    virtual void updateWithInstruction(const llvm::ICmpInst & instruction);
    virtual void updateWithInstruction(const llvm::FCmpInst & instruction);
    virtual void updateWithInstruction(const llvm::AllocaInst & instruction);
    virtual void updateWithInstruction(const llvm::LoadInst & instruction);
    */
    virtual void updateWithInstruction(const llvm::StoreInst & instruction);
    /*
    virtual void updateWithInstruction(const llvm::GetElementPtrInst & instruction);
    virtual void updateWithInstruction(const llvm::InsertValueInst & instruction);
    virtual void updateWithInstruction(const llvm::ExtractValueInst & instruction);
    virtual void updateWithInstruction(const llvm::AtomicRMWInst & instruction);
    virtual void updateWithInstruction(const llvm::ExtractElementInst & instruction);
    virtual void updateWithInstruction(const llvm::InsertElementInst & instruction);
    virtual void updateWithInstruction(const llvm::ShuffleVectorInst & instruction);
    */

    virtual void updateStore(
		const llvm::Value & baseValue, const llvm::Value & valueValue,
		std::map<klee::ref<klee::Expr>, klee::ref<klee::Expr> > & memmap);
    virtual void update(const llvm::BasicBlock & basicBlock);
    virtual void update(const llvm::Instruction & instruction);

    virtual klee::ref<klee::Expr> _evaluate(const llvm::Value & value) ;
    virtual klee::ref<klee::Expr> _evaluate(const llvm::LoadInst & instruction);
    virtual klee::ref<klee::Expr> _evaluate(const llvm::Argument & argument) ;
    virtual klee::ref<klee::Expr> _evaluate(const llvm::GlobalValue & globalValue);

public:
    static Summary & get(const llvm::Function * f);
    Summary();
    // Summary(const Summary &) = default;
    // Summary(Summary &&) = default;
    virtual void update(const llvm::Function & function);
    virtual klee::ref<klee::Expr> evaluate(const llvm::Value & value) ;
    virtual klee::ref<klee::Expr> createSymbolicExpr(LLVM_TYPE_Q llvm::Type * type, const std::string & name) const;
    // TODO(oanson) Make these methods consts
    bool hasReturnValue() const ;
    // Representatives of the arguments
    const std::vector<klee::ref<klee::Expr> > & arguments() const;
    // Representatives of globals
    const std::map<const llvm::GlobalValue *, klee::ref<klee::Expr> > & globals() const;
    // The return value
    const klee::ref<klee::Expr> & returnValue() const;
    // Modified memory addresses, and their values
    std::map<klee::ref<klee::Expr>, klee::ref<klee::Expr> > & modifiedMemory();
    // The function being summarised
    const llvm::Function & function() const;

    virtual void print(std::ostream&) const;
    virtual void debug() const;
};

class SummaryExecution {
protected:
	std::map<klee::ref<klee::ArgumentExpr>, klee::ref<klee::Expr> > _arguments;
	std::map<klee::ref<klee::PureSymbolicExpr>, klee::ref<klee::Expr> > _symbolics;
public:
	const Summary & summary;
	const klee::ConstraintManager constraints;
	SummaryExecution(const Summary & summary, const klee::ConstraintManager & constraints);
	const std::map<klee::ref<klee::ArgumentExpr>, klee::ref<klee::Expr> > & arguments() const;
	const std::map<klee::ref<klee::PureSymbolicExpr>, klee::ref<klee::Expr> > & symbolics() const;

	void map(klee::ref<klee::ArgumentExpr> &key, klee::ref<klee::Expr> & value);
	void map(klee::ref<klee::PureSymbolicExpr> &key, klee::ref<klee::Expr> & value);
};

/*
class SummaryWithConstraints : public Summary {
protected:
	klee::ConstraintManager _constraintManager;
public:
	SummaryWithConstraints() : Summary() {}
};
*/

inline std::ostream & operator<<(std::ostream & os, const Summary & summary) {
	summary.print(os);
	return os;
}

inline llvm::raw_ostream & operator<<(llvm::raw_ostream & os, const Summary & summary) {
	std::stringstream ss;
	ss << summary;
	os << ss.str();
	return os;
}

#endif /* KLEE_SUMMARY_H */
