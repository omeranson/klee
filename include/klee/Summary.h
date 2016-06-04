
#include <map>
#include <string>

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>


class Summary {
    // ...
protected:
    const klee::ExecutionState & _state;
    const klee::Executor & _executor;
    bool _hasReturnValue;
    ref<Expr> _returnValue;
    std::map<ref<Expr>, ref<Expr> > _modifiedMemory;
    std::string _functionName;

    virtual void updateWithInstruction(llvm::Instruction * instruction);
    virtual void updateWithInstruction(llvm::ReturnInst * instruction);
    /*
    virtual void updateWithInstruction(llvm::BranchInst * instruction);
    virtual void updateWithInstruction(llvm::SwitchInst * instruction);
    virtual void updateWithInstruction(llvm::InvokeInst * instruction);
    virtual void updateWithInstruction(llvm::CallInst * instruction);
    virtual void updateWithInstruction(llvm::PHINode * instruction);
    virtual void updateWithInstruction(llvm::SelectInst * instruction);
    virtual void updateWithInstruction(llvm::BinaryOperator * instruction);
    virtual void updateWithInstruction(llvm::UnaryInstruction * instruction);
    virtual void updateWithInstruction(llvm::ICmpInst * instruction);
    virtual void updateWithInstruction(llvm::FCmpInst * instruction);
    virtual void updateWithInstruction(llvm::AllocaInst * instruction);
    virtual void updateWithInstruction(llvm::LoadInst * instruction);
    virtual void updateWithInstruction(llvm::StoreInst * instruction);
    virtual void updateWithInstruction(llvm::GetElementPtrInst * instruction);
    virtual void updateWithInstruction(llvm::InsertValueInst * instruction);
    virtual void updateWithInstruction(llvm::ExtractValueInst * instruction);
    virtual void updateWithInstruction(llvm::AtomicRMWInst * instruction);
    virtual void updateWithInstruction(llvm::ExtractElementInst * instruction);
    virtual void updateWithInstruction(llvm::InsertElementInst * instruction);
    virtual void updateWithInstruction(llvm::ShuffleVectorInst * instruction);
    */

    virtual void update(llvm::BasicBlock & basicBlock);
    virtual void update(llvm::Instruction & instruction);
public:
    Summary(const klee::ExecutionState &, const klee::Executor &);
    virtual void update(llvm::Function & function);
    // TODO(oanson) Make these methods consts
    bool hasReturnValue() const ;
    // The return value
    ref<Expr> & returnValue() ;
    // Modified memory addresses, and their values
    std::map<ref<Expr>, ref<Expr> > & modifiedMemory();

    void debug() const;
};

