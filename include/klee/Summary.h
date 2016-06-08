#ifndef KLEE_SUMMARY_H
#define KLEE_SUMMARY_H

#include <map>
#include <string>
#include <vector>

#include "klee/Common.h"
#include "klee/Constraints.h"
#include "klee/ExecutionState.h"
#include "klee/util/ArrayCache.h"
#include "Executor.h"

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
    std::vector<klee::ref<klee::Expr> > _arguments;
    std::string _functionName;
    klee::ArrayCache & _arrayCache;
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

    virtual klee::ref<klee::Expr> _evaluate(const llvm::Value & value) const;
    virtual klee::ref<klee::Expr> _evaluate(const llvm::LoadInst & instruction) const;
    virtual klee::ref<klee::Expr> _evaluate(const llvm::Argument & argument) const;
public:
    Summary(klee::ArrayCache & arrayCache);
    virtual void update(const llvm::Function & function);
    virtual klee::ref<klee::Expr> evaluate(const llvm::Value & value) const;
    virtual klee::ref<klee::Expr> createSymbolicExpr(LLVM_TYPE_Q llvm::Type * type, const std::string & name) const;
    // TODO(oanson) Make these methods consts
    bool hasReturnValue() const ;
    // Representatives of the arguments
    std::vector<klee::ref<klee::Expr> > & arguments();
    // The return value
    klee::ref<klee::Expr> & returnValue() ;
    // Modified memory addresses, and their values
    std::map<klee::ref<klee::Expr>, klee::ref<klee::Expr> > & modifiedMemory();

    virtual void debug() const;
};
/*
class SummaryWithConstraints : public Summary {
protected:
	klee::ConstraintManager _constraintManager;
public:
	SummaryWithConstraints() : Summary() {}
};
*/

#endif /* KLEE_SUMMARY_H */
