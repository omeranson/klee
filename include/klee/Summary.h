#ifndef KLEE_SUMMARY_H
#define KLEE_SUMMARY_H

#include <map>
#include <string>

#include "klee/Common.h"
#include "klee/ExecutionState.h"
#include "klee/util/ArrayCache.h"
#include "Executor.h"

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>


class Summary {
    // ...
protected:
    const klee::ExecutionState & _state;
    const klee::Executor & _executor;
    bool _hasReturnValue;
    klee::ref<klee::Expr> _returnValue;
    std::map<klee::ref<klee::Expr>, klee::ref<klee::Expr> > _modifiedMemory;
    std::string _functionName;
    klee::ArrayCache arrayCache;

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
    virtual void updateWithInstruction(const llvm::StoreInst & instruction);
    virtual void updateWithInstruction(const llvm::GetElementPtrInst & instruction);
    virtual void updateWithInstruction(const llvm::InsertValueInst & instruction);
    virtual void updateWithInstruction(const llvm::ExtractValueInst & instruction);
    virtual void updateWithInstruction(const llvm::AtomicRMWInst & instruction);
    virtual void updateWithInstruction(const llvm::ExtractElementInst & instruction);
    virtual void updateWithInstruction(const llvm::InsertElementInst & instruction);
    virtual void updateWithInstruction(const llvm::ShuffleVectorInst & instruction);
    */

    virtual void update(const llvm::BasicBlock & basicBlock);
    virtual void update(const llvm::Instruction & instruction);
public:
    Summary(const klee::ExecutionState &, const klee::Executor &);
    virtual void update(const llvm::Function & function);
    // TODO(oanson) Make these methods consts
    bool hasReturnValue() const ;
    // The return value
    klee::ref<klee::Expr> & returnValue() ;
    // Modified memory addresses, and their values
    std::map<klee::ref<klee::Expr>, klee::ref<klee::Expr> > & modifiedMemory();

    virtual void debug() const;
};

#endif /* KLEE_SUMMARY_H */
